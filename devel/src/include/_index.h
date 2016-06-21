/* _index.h defines the index structure and declares internal functions 
 *
 * written nml 2003-06-02
 *
 */

/* can't use _INDEX_H because names with underscore are reserved for compiler */
#ifndef PRIVATE_INDEX_H
#define PRIVATE_INDEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zettair.h"

#include "index.h"
#include "storagep.h"
#include "stream.h"
#include "vocab.h"
#include "zpthread.h"

enum index_flags {
    INDEX_BUILT = (1 << 0),             /* the index has been constructed */
    INDEX_STEMMED = (3 << 3),           /* mask to tell whether index is stemmed */
    INDEX_STEMMED_PORTERS = (1 << 3),   /* whether its stemmed with porter's stemmer */
    INDEX_STEMMED_EDS = (1 << 4),       /* whether its stemmed with eds stemmer */
    INDEX_STEMMED_LIGHT = (3 << 3)      /* whether its stemmed with the light stemmer */
};

/* structure holding all members that are required on a per-query basis.
 * We maintain a list of them, so that parellel queries can grab one per-query
 * structure and proceed on without interference. */
struct index_perquery {
    struct index_perquery *next;
    struct summarise *sum;
};

struct index {
    enum index_flags flags;             /* flags to indicate various global 
                                         * states of the index */

    unsigned int repos;                 /* number of repositories */
    unsigned int vectors;               /* number of vector files */
    unsigned int vocabs;                /* number of vocab files */
    unsigned long int repos_pos;        /* byte position of the last repos_fd */

    struct fdset *fd;                   /* dynamic file descriptor set for all 
                                         * index/repository files */
    struct iobtree *vocab;              /* vocabulary */
    struct docmap *map;                 /* document map */
    struct psettings *settings;         /* parser settings */

    struct stem_cache *stem;            /* stemmer cache (or NULL) */
    struct stop *istop;                 /* construction stoplist (or NULL) */
    struct stop *qstop;                 /* query stoplist (or NULL) */

    struct index_perquery *perquery;    /* stuff required to evaluate queries 
                                         * in parellel */

    /* locks for multithreaded stuff.  Note that we use hierarchical locking 
     * to avoid deadlock, in order, from first-obtained to last-obtained, that
     * they appear below.  Some of the structures (notably the fdset) have
     * internal locks, but they should play nicely with this scheme, so long 
     * as locks are acquired before any accesses to them are attempted */

    struct mrwlock *biglock;            /* big lock, which controls multi-threaded access
                                           (though not necessarily exclusive access) to the index */
    zpthread_mutex_t vocab_mutex;       /* mutex which controls access to the vocabulary structure */
    zpthread_mutex_t docmap_mutex;      /* mutex which controls access to the docmap structure */
    zpthread_mutex_t perquery_mutex;    /* mutex controlling access to the perquery list */

    /* construction stuff */
    struct postings *post;              /* accumulated in-memory postings */
    struct pyramid *merger;             /* pointers to dumped postings */
    struct storagep storage;            /* storage parameters */

    /* 'types' for accessing files through the fdset */
    unsigned int param_type;            /* index parameter file type */
    unsigned int index_type;            /* index fileset type */
    unsigned int repos_type;            /* repos fileset type */
    unsigned int tmp_type;              /* temporary fileset type */
    unsigned int vtmp_type;             /* temporary vocabulary fileset type */
    unsigned int vocab_type;            /* vocab btree fileset type */
    unsigned int docmap_type;           /* docmap fileset type */

    struct {
        unsigned int parsebuf;          /* size of parse buffer */
        unsigned int tblsize;           /* size of postings hashtable */
        unsigned int memory;            /* how much memory we can use */
        char *config;                   /* configuration file location (or NULL for built-in configuration) */
    } params;

    struct {
        unsigned int updates;           /* number of updates index has 
                                         * undergone */
        double avg_weight;              /* average document weight */
        double avg_length;              /* average document length in bytes */

        /* total number of term occurrances */
        unsigned int terms_high;        /* high word */
        unsigned int terms_low;         /* low word */
    } stats;

    struct imp_stats {
        double avg_f_t;                 /* average term frequency */
        double slope;                   /* used in normalising */
        unsigned int quant_bits;        /* used in quantising */
        double w_qt_min;
        double w_qt_max;
    } impact_stats;                     /* statistics required at query time for impact ordered vectors */

    enum vocab_vtype vector_types;      /* types of vectors available in this index */
};

/* internal function to merge the current postings into the index */
int index_remerge(struct index *idx, unsigned int commitopts, struct index_commit_opt *commitopt);

/* internal function to atomically perform a read */
ssize_t index_atomic_read(int fd, void *buf, unsigned int size);

/* internal function to atomically perform a write */
ssize_t index_atomic_write(int fd, void *buf, unsigned int size);

/* write the header block of the index to disk. */
int index_commit_superblock(struct index *idx);

/* exactly the same as index_commit, except doesn't bugger around with restoring
 * indexes to exact on-disk representation */
int index_commit_internal(struct index *idx, unsigned int opts, struct index_commit_opt *opt, unsigned int addopts, struct index_add_opt *addopt);

/* function to return the stemming function used by an index */
void (*index_stemmer(struct index *idx))(void *, char *);

/* utility function to read into a stream from a file/buffer */
enum stream_ret index_stream_read(struct stream *instream, int fd, char *buf, unsigned int bufsize);

/* functions to allocate and delete perquery objects */
struct index_perquery *index_perquery_new(struct index *idx);
void index_perquery_delete(struct index_perquery *perquery);

/* functions to fetch and store perquery objects in the idx->perquery list */
struct index_perquery *index_perquery_fetch(struct index *idx);
int index_perquery_store(struct index *idx, struct index_perquery *perquery);

#ifdef __cplusplus
}
#endif

#endif

