/* objalloc.c implements an object that efficiently returns allocations of a 
 * set size.  Our implementation is fairly simple, in that we request memory
 * from the underlying allocation mechanism in chunks of (at least) a given 
 * size.  Once a chunk has been allocated, memory is freshly allocated from 
 * that chunk in preference to returning previously allocated memory from the
 * linked list.  This optimises bulk allocation and freeing of objects, slowing
 * allocate-one-free-one style allocation.  Once the allocator has run out of
 * fresh memory to allocate, it returns freed objects until it runs out of them,
 * and then allocates a new chunk.
 *
 * written nml 2004-08-30
 *
 */

/* FIXME:
     - restore redzones
     - drain can be subsumed into reserve
     - ptr arg to _memsize? (something to do with alloc interface?)
 */

#include "firstinclude.h"

#include "objalloc.h"

#include "alloc.h"
#include "def.h"
#include "mem.h"
#include "_mem.h"
#include "zvalgrind.h"

#include <assert.h>

/* integer value we use to fill up space */
#define SPACE_FILL 0xdeadbeefU

#define FILL_BYTE(i) ((unsigned char) (SPACE_FILL >> (8 * (3 - ((i) % 4)))))

struct objalloc_chunk { 
    char *pos;                       /* next free position in this chunk */
    char *end;                       /* pointer to the end of the chunk */
    struct objalloc_chunk *next;     /* linked list of chunks */
    unsigned int size;               /* size of chunk, excluding header */
    /* more memory than this is allocated, and is managed below */
};

struct objalloc_object {
    struct objalloc_object *next;     /* linked list of objects */
};

struct objalloc {
    struct objalloc_chunk chunk;     /* chunk currently being allocated from,
                                      * followed by chunks that have been fully
                                      * allocated.  Note that this is not a
                                      * pointer.  Chunk headers are copied in
                                      * and out of this member as they become
                                      * active or exhausted, so as to minimise
                                      * indirection when allocating. */
    struct objalloc_object *free;    /* list of free locations */

    struct objalloc_chunk *reserved; /* reserved chunks (those that have not 
                                      * serviced any allocations yet) */
    struct alloc alloc;              /* underlying allocator */
    unsigned int allocsize;          /* size of objects we're allocating */
    unsigned int redzone;            /* size of redzone we're putting after 
                                      * objects */
    unsigned int chunksize;          /* size of chunks we're requesting from 
                                      * the underlying allocation mechanism */
    unsigned int allocated;          /* how many objects are currently 
                                      * allocated */
    unsigned int align;              /* object alignment */
};

/* macro to detect the first chunk of the object allocator (that shares space
 * with the aggregate header).  Note that this method works even when the chunk
 * is copied into the aggregate header. */
#define IS_FIRST_CHUNK(obj, chunk) \
  ((((char *) (obj)) + (obj)->chunksize) == ((chunk)->end))

/* macro to return the memory position of the true header of a given chunk */
#define CHUNK_ADDR(chunk) ((struct objalloc_chunk *) \
  (((char *) (chunk)->end) - (chunk)->size - sizeof(*(chunk))))

static int is_first_chunk(struct objalloc *obj, struct objalloc_chunk *chunk) {
    return IS_FIRST_CHUNK(obj, chunk);
}

static struct objalloc_chunk *chunk_addr(struct objalloc_chunk *chunk) {
    return CHUNK_ADDR(chunk);
}

static int objalloc_invariant(struct objalloc *obj) {
    struct objalloc_chunk *chunk = &obj->chunk,
                          *next;

    if (!DEAR_DEBUG) {
        return 1;
    }

    /* process active and exhausted chunks */
    do {
        VALGRIND_MAKE_READABLE(chunk, sizeof(*chunk));
        VALGRIND_MAKE_READABLE(CHUNK_ADDR(chunk), sizeof(*chunk));
        next = chunk->next;

        /* if it isn't the aggregate chunk, it should be exhausted */
        if (chunk != &obj->chunk) {
            if (chunk->pos <= chunk->end - (obj->allocsize + obj->redzone)) {
                assert("failed invariant" && 0);
                return 0;
            }
        }

        /* check that the size is laid out sensibly */
        if (chunk != &obj->chunk) {
            if ((char *) chunk->end 
              != ((char *) chunk) + chunk->size + sizeof(*chunk)) {
                assert("failed invariant" && 0);
                return 0;
            }
        }
        if (chunk->pos < chunk->end - chunk->size) {
            assert("failed invariant" && 0);
            return 0;
        }

        /* check that this chunk doesn't overlap the next */
        if (next) {
            VALGRIND_MAKE_READABLE(next, sizeof(*next));
            if (!((void *) next->end <= (void *) CHUNK_ADDR(chunk) 
              || (void *) next >= (void *) (CHUNK_ADDR(chunk))->end)) {
                assert("failed invariant" && 0);
                return 0;
            }
            VALGRIND_MAKE_NOACCESS(next, sizeof(*next));
        }

        /* check that the space on this chunk is sensible */
        if (chunk->pos > chunk->end 
          || chunk->pos < chunk->end - chunk->size) {
            assert("failed invariant" && 0);
            return 0;
        }

        if (!next) {
            assert(is_first_chunk(obj, chunk));
            assert((void *) CHUNK_ADDR(chunk) == (void *) (obj + 1));
        } else {
            assert(chunk_addr(chunk) == chunk 
              || (void *) chunk == (void *) obj);
        }
        VALGRIND_MAKE_NOACCESS(CHUNK_ADDR(chunk), sizeof(*chunk));
        VALGRIND_MAKE_NOACCESS(chunk, sizeof(*chunk));
    } while ((chunk = next));

    /* process reserved chunks */
    next = obj->reserved;
    while ((chunk = next)) {
        VALGRIND_MAKE_READABLE(chunk, sizeof(*chunk));
        next = chunk->next;
        assert(chunk->pos < chunk->end);
        assert(chunk->pos == chunk->end - chunk->size);
        VALGRIND_MAKE_NOACCESS(chunk, sizeof(*chunk));
    }

    return 1;
}

/* internal function to initialise members of a new chunk */
static void chunk_init(struct objalloc *obj, struct objalloc_chunk *chunk, 
  void *start, unsigned int size, struct objalloc_chunk *next) {
    assert(size);
    assert(size >= obj->allocsize + obj->redzone);
    chunk->next = next;
    chunk->pos = start;
    chunk->size = size - sizeof(*chunk);
    chunk->end = chunk->pos + chunk->size;
    assert(chunk->pos < chunk->end);
    VALGRIND_MAKE_NOACCESS(chunk->pos, chunk->size);
    VALGRIND_MAKE_NOACCESS(chunk, sizeof(*chunk));
}

struct objalloc *objalloc_new(unsigned int size, unsigned int align, 
  unsigned int redzone, unsigned int bulkalloc, const struct alloc *alloc) {
    struct objalloc *obj;
    unsigned int min;

    /* don't allow 0 sized objects, it doesn't make any sense */
    if (!size) {
        return NULL;
    }

    if (!alloc) {
        alloc = &alloc_system;
    }

    if (!align) {
        align = mem_align_max();
    }

    /* ensure that size is a multiple of the alignment, and is big enough to
     * store a pointer. */
    if (size < sizeof(struct objalloc_object)) {
        size = sizeof(struct objalloc_object);
    }
    if (align * (size / align) != size) {
        /* round up to nearest alignment boundary */
        size = align * (size / align + 1);
    }

    /* figure out redzone allowing for alignment */
    redzone = ((redzone + (align - 1)) / align) * align;

    /* figure out minimum size that we need bulkalloc to be to allocate the
     * object, a chunk header, one redzone and one object */
    min = sizeof(struct objalloc) + sizeof(struct objalloc_chunk) 
      + size + redzone;
    if (bulkalloc < min) {
        bulkalloc = min;
    }

    if ((obj = alloc->malloc(alloc->opaque, bulkalloc))) {
        obj->align = align;
        obj->allocsize = size;
        obj->redzone = redzone;
        obj->chunksize = bulkalloc;
        obj->reserved = NULL;
        obj->free = NULL;
        obj->allocated = 0;
        obj->alloc = *alloc;

        /* set up first chunk (first chunk starts immediately after object
         * header in memory, first allocated position starts immediately after
         * first chunk header).  Note that this a little deceptive, because we
         * aren't using the first chunk header yet, as it is 'copied' into the
         * immediate member in the object header. */
        VALGRIND_MAKE_NOACCESS(obj + 1, sizeof(obj->chunk));
        chunk_init(obj, &obj->chunk, ((char *) (obj + 1)) + sizeof(obj->chunk),
          bulkalloc - sizeof(*obj), NULL);

        if (!objalloc_invariant(obj)) {
            objalloc_delete(obj);
            obj = NULL;
        }
    }

    return obj;
}

void objalloc_delete(struct objalloc *obj) {
    struct objalloc_chunk *chunk = &obj->chunk,
                          *next;

    assert(objalloc_invariant(obj));

    do {
        VALGRIND_MAKE_READABLE(chunk, sizeof(*chunk));
        next = chunk->next;
        assert(chunk->pos >= chunk->end - chunk->size);
        if (!IS_FIRST_CHUNK(obj, chunk)) {
            assert((void *) obj != (void *) CHUNK_ADDR(chunk));
            obj->alloc.free(obj->alloc.opaque, CHUNK_ADDR(chunk));
        }
    } while ((chunk = next));

    /* free reserved blocks */
    for (chunk = obj->reserved; chunk; chunk = next) {
        VALGRIND_MAKE_READABLE(chunk, sizeof(*chunk));
        next = chunk->next;
        assert(!IS_FIRST_CHUNK(obj, chunk));
        assert(CHUNK_ADDR(chunk) == chunk);
        obj->alloc.free(obj->alloc.opaque, chunk);
    }

    obj->alloc.free(obj->alloc.opaque, obj);
}

void *objalloc_malloc(struct objalloc *obj, unsigned int size) {
    void *ptr;

    if (size <= obj->allocsize) {
        VALGRIND_MAKE_READABLE(&obj->chunk, sizeof(obj->chunk));
        if (obj->chunk.pos + obj->allocsize + obj->redzone <= obj->chunk.end) {
            /* allocate from current chunk */
            ptr = obj->chunk.pos;
            obj->chunk.pos += obj->allocsize;
            VALGRIND_MALLOCLIKE_BLOCK(ptr, obj->allocsize, 0, 0);

            obj->chunk.pos += obj->redzone;
            obj->allocated++;
            VALGRIND_MAKE_NOACCESS(&obj->chunk, sizeof(obj->chunk));
            return ptr;
        } else if (obj->free) {
            VALGRIND_MAKE_NOACCESS(&obj->chunk, sizeof(obj->chunk));

            /* allocate from free list */
            ptr = obj->free;
            VALGRIND_MAKE_READABLE(obj->free, sizeof(*obj->free));
            obj->free = obj->free->next;
            VALGRIND_MALLOCLIKE_BLOCK(ptr, obj->allocsize, 0, 0);


            obj->allocated++;
            return ptr;
        } else if (obj->reserved || ((obj->reserved = obj->alloc.malloc(obj->alloc.opaque, obj->chunksize))
                && (chunk_init(obj, obj->reserved, obj->reserved + 1, obj->chunksize, NULL), 1))) {

            struct objalloc_chunk *chunk, *next;

            /* note that objalloc_invariant reprotects all chunks */
            assert(objalloc_invariant(obj));
            VALGRIND_MAKE_READABLE(obj->reserved, sizeof(*obj->reserved));
            VALGRIND_MAKE_READABLE(&obj->chunk, sizeof(obj->chunk));

            /* copy exhausted chunk out into indirect header */
            chunk = CHUNK_ADDR(&obj->chunk);
            VALGRIND_MAKE_READABLE(chunk, sizeof(*chunk));
            *chunk = obj->chunk;

            /* copy new chunk into aggregate header */
            obj->chunk = *obj->reserved;
            next = (obj->reserved) ? obj->reserved->next : NULL;
            obj->chunk.next = chunk;  /* link to exhausted chunks */
            obj->reserved = next;

            /* recursively allocate, because it prevents code duplication,
             * happens very rarely, and doesn't ever recurse further */
            assert(obj->chunk.pos + obj->allocsize + obj->redzone <= obj->chunk.end);
            VALGRIND_MAKE_NOACCESS(CHUNK_ADDR(&obj->chunk), sizeof(obj->chunk));
            VALGRIND_MAKE_NOACCESS(chunk, sizeof(*chunk));
            VALGRIND_MAKE_NOACCESS(&obj->chunk, sizeof(obj->chunk));
            assert(objalloc_invariant(obj));
            return objalloc_malloc(obj, size);
        }
    } 

    return NULL;
}

void objalloc_free(struct objalloc *obj, void *ptr) {
    if (!ptr)
        return;

    struct objalloc_object *object = ptr;

    assert(objalloc_is_managed(obj, ptr));
    assert(obj->allocated);
    object->next = obj->free;
    obj->free = object;
    VALGRIND_FREELIKE_BLOCK(ptr, 0);
    obj->allocated--;
    assert(objalloc_invariant(obj));
    return;
}

void *objalloc_realloc(struct objalloc *obj, void *ptr, unsigned int size) {
    if (size) {
        if (ptr) {
            assert(objalloc_is_managed(obj, ptr));

            if (size <= obj->allocsize) {
                return ptr;
            }
        } else {
            return objalloc_malloc(obj, size);
        }
    } else {
        objalloc_free(obj, ptr);
    }

    return NULL;
}

void objalloc_clear(struct objalloc *obj) {
    struct objalloc_chunk *chunk = &obj->chunk,
                          *next,
                          *indirect;

    assert(objalloc_invariant(obj));

    if (RUNNING_ON_VALGRIND) {
        struct objalloc_object *object;

        /* first, allocate all of the freed objects, so that we can free all
         * possibly allocated chunks without worrying about which ones have 
         * already been returned */
        for (object = obj->free; object; object = object->next) {
            VALGRIND_MALLOCLIKE_BLOCK(object, obj->allocsize, 0, 1);
        }
    }

    /* free all allocated objects */
    do {
        char *pos;
        unsigned int frees = 0, predicted;
   
        VALGRIND_MAKE_READABLE(chunk, sizeof(*chunk));

        next = chunk->next;

        if (RUNNING_ON_VALGRIND) {
            pos = chunk->end - chunk->size;
            predicted = (chunk->pos - pos)/(obj->allocsize + obj->redzone);

            assert(pos <= chunk->pos);
            while (pos < chunk->pos) {
                /* ensure that the address we've calculated is valid */
                assert(objalloc_is_managed(obj, pos));

                VALGRIND_FREELIKE_BLOCK(pos, 0);
                pos += obj->allocsize + obj->redzone;
                frees++;
            }
            assert(frees == predicted);
        }
 
        /* reset pos within chunk */
        chunk->pos = chunk->end - chunk->size;
        VALGRIND_MAKE_NOACCESS(chunk->pos, chunk->size);
        VALGRIND_MAKE_NOACCESS(chunk, sizeof(*chunk));
    } while (chunk = next);

    /* clear list of free objects, as they are absorbed back into the chunks */
    obj->free = NULL;  
    obj->allocated = 0;

    /* place chunk in aggregate back onto reserved list */
    VALGRIND_MAKE_READABLE(&obj->chunk, sizeof(obj->chunk));
    indirect = CHUNK_ADDR(&obj->chunk);
    VALGRIND_MAKE_READABLE(indirect, sizeof(*indirect));
    *indirect = obj->chunk;
    indirect->next = obj->reserved;
    obj->reserved = indirect;
    VALGRIND_MAKE_NOACCESS(indirect, sizeof(*indirect));

    /* place chunks on exhausted list back onto reserved list */
    while (obj->chunk.next) {
        VALGRIND_MAKE_READABLE(obj->chunk.next, sizeof(obj->chunk));
        next = obj->chunk.next->next;
        obj->chunk.next->next = obj->reserved;
        obj->reserved = obj->chunk.next;
        VALGRIND_MAKE_NOACCESS(obj->chunk.next, sizeof(obj->chunk));
        obj->chunk.next = next;
    }

    /* copy first element on reserved list back into aggregate header
     * (note that it should be the first chunk) */
    VALGRIND_MAKE_READABLE(obj->reserved, sizeof(*indirect));
    assert(IS_FIRST_CHUNK(obj, obj->reserved));
    obj->chunk = *obj->reserved;
    obj->reserved = obj->reserved->next;
    VALGRIND_MAKE_NOACCESS(obj->reserved, sizeof(*indirect));
    obj->chunk.next = NULL;
    VALGRIND_MAKE_NOACCESS(&obj->chunk, sizeof(obj->chunk));

    assert(objalloc_invariant(obj));
    return;
}

void objalloc_drain(struct objalloc *obj) {
    struct objalloc_chunk *chunk,
                          *next = obj->reserved;

    while ((chunk = next)) {
        next = chunk->next;
        obj->alloc.free(obj->alloc.opaque, chunk);
    }

    obj->reserved = NULL;
    return;
}

unsigned int objalloc_reserve(struct objalloc *obj, unsigned int reserve) {
    struct objalloc_chunk *chunk,
                          *next = obj->reserved;
    unsigned int reserved = 0,
                 size;

    while ((chunk = next)) {
        next = chunk->next;
        reserved += chunk->size / (obj->allocsize + obj->redzone);
    }

    /* attempt to allocate one chunk to satisfy entire reserve, ignoring size
     * restriction */
    size = (reserved - reserve) * (obj->allocsize + obj->redzone) 
      + sizeof(*chunk) > obj->chunksize;
    if (reserved < reserve && (size > obj->chunksize)
      && (chunk = obj->alloc.malloc(obj->alloc.opaque, size))) {
        chunk_init(obj, chunk, chunk + 1, size, obj->reserved);
        obj->reserved = chunk;

        reserved += (size - sizeof(*chunk)) / (obj->allocsize + obj->redzone);
        assert(reserved == reserve);
    }

    while (reserved < reserve 
      && (chunk = obj->alloc.malloc(obj->alloc.opaque, obj->chunksize))) {
        chunk_init(obj, chunk, chunk + 1, obj->chunksize, obj->reserved);
        obj->reserved = chunk;

        reserved += (obj->chunksize - sizeof(*chunk)) 
          / (obj->allocsize + obj->redzone);
    }

    return reserved;
}

int objalloc_is_managed(struct objalloc *obj, void *ptr) {
    struct objalloc_chunk *chunk = &obj->chunk,
                          *next;

    do {
        VALGRIND_MAKE_READABLE(chunk, sizeof(*chunk));
        next = chunk->next;

        if (ptr < (void *) chunk->pos 
          && ptr >= (void *) (chunk->end - chunk->size)) {
            return 1;
        }

        VALGRIND_MAKE_NOACCESS(chunk, sizeof(*chunk));
    } while ((chunk = next));

    return 0;
}

unsigned int objalloc_allocated(struct objalloc *obj) {
    return obj->allocated;
}

unsigned int objalloc_objsize(struct objalloc *obj) {
    return obj->allocsize;
}

unsigned int objalloc_overhead_first(void) {
    return sizeof(struct objalloc) + sizeof(struct objalloc_chunk);
}

unsigned int objalloc_overhead(void) {
    return sizeof(struct objalloc_chunk);
}

unsigned int objalloc_memsize(struct objalloc *obj, void *ptr) {
    struct objalloc_chunk *chunk,
                          *next;
    unsigned int size = sizeof(*obj);

    chunk = &obj->chunk;
    do {
        size += chunk->size + sizeof(*chunk);
        next = chunk->next;
    } while ((chunk = next));

    return size;
}

#ifdef OBJALLOC_TEST

#include <stdlib.h>

int main() {
    unsigned int i;
    int *arr[20];
    struct objalloc *alloc;

    /* just alloc and free */

    alloc = objalloc_new(sizeof(int), 0, 1, 10 * sizeof(int), NULL);
    assert(alloc);

    for (i = 0; i < 20; i++) {
        arr[i] = objalloc_malloc(alloc, sizeof(int));
        *arr[i] = i;
    }
    assert(!objalloc_malloc(alloc, sizeof(int) + 1));

    for (i = 0; i < 20; i++) {
        assert(*arr[i] == i);
        objalloc_free(alloc, arr[i]);
    }

    objalloc_delete(alloc); 

    /* different sizes */

    alloc = objalloc_new(sizeof(int), 0, 1, 10 * sizeof(int), NULL);
    assert(alloc);

    for (i = 0; i < 20; i++) {
        arr[i] = objalloc_malloc(alloc, i);
        if (i <= sizeof(int)) {
            assert(arr[i]);
            arr[i] = objalloc_realloc(alloc, arr[i], i);
            if (i) {
                assert(arr[i]);
            } else {
                assert(!arr[i]);
            }
        } else {
            assert(!arr[i]);
        }
    }
    assert(!objalloc_malloc(alloc, sizeof(int) + 1));

    for (i = 0; i < 20; i++) {
        objalloc_free(alloc, arr[i]);
    }

    objalloc_delete(alloc); 

    /* test drain */

    alloc = objalloc_new(sizeof(int), 0, 1, 10 * sizeof(int), NULL);
    assert(alloc);

    for (i = 0; i < 20; i++) {
        arr[i] = objalloc_malloc(alloc, sizeof(int));
        *arr[i] = i;
    }
    assert(!objalloc_malloc(alloc, sizeof(int) + 1));

    for (i = 0; i < 20; i++) {
        assert(*arr[i] == i);
        objalloc_free(alloc, arr[i]);
    }

    objalloc_drain(alloc);

    for (i = 0; i < 20; i++) {
        arr[i] = objalloc_malloc(alloc, sizeof(int));
        *arr[i] = i;
    }
    assert(!objalloc_malloc(alloc, sizeof(int) + 1));

    for (i = 0; i < 20; i++) {
        assert(*arr[i] == i);
        objalloc_free(alloc, arr[i]);
    }

    objalloc_drain(alloc);

    objalloc_delete(alloc); 

    /* perform some invalid accesses */

    alloc = objalloc_new(sizeof(int), 0, 1, 10 * sizeof(int), NULL);
    assert(alloc);

    for (i = 0; i < 20; i++) {
        arr[i] = objalloc_malloc(alloc, sizeof(int));
        *arr[i] = i;
    }

    /* valid access */
    *arr[0] = 0;

    /* FIXME: invalid accesses 
    i = arr[0][-1];
    arr[1][-1] = -1;
    arr[1][1] = -1; */

    for (i = 0; i < 20; i++) {
        assert(*arr[i] == i);
        objalloc_free(alloc, arr[i]);
    }

    objalloc_clear(alloc);
    objalloc_delete(alloc);

    /* cause leaks */

    alloc = objalloc_new(sizeof(int), 0, 1, 10 * sizeof(int), NULL);
    assert(alloc);

    for (i = 0; i < 20; i++) {
        arr[i] = objalloc_malloc(alloc, sizeof(int));
        *arr[i] = i;
    }

    for (i = 1; i < 19; i++) {
        assert(*arr[i] == i);
        objalloc_free(alloc, arr[i]);
    }

    /* objalloc_clear(alloc); */
    objalloc_delete(alloc);

    /* use clear */

    alloc = objalloc_new(sizeof(int), 0, 1, 10 * sizeof(int), NULL);
    assert(alloc);

    for (i = 0; i < 20; i++) {
        arr[i] = objalloc_malloc(alloc, sizeof(int));
        *arr[i] = i;
    }

    objalloc_clear(alloc);

    for (i = 0; i < 20; i++) {
        arr[i] = objalloc_malloc(alloc, sizeof(int));
        *arr[i] = i;
    }

    objalloc_clear(alloc);
    objalloc_delete(alloc); 

    return EXIT_SUCCESS;
}

#endif

