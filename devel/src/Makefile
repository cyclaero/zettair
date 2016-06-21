# Makefile for FreeBSD using LLVM/clang
#
# Usage examples:
#   make
#   make clean
#   make update
#   make install clean
#   make clean install CDEFS="-DDEBUG"

.if exists(.svn) || exists(../.svn) || exists(../../.svn) || exists(../../../.svn)
.ifmake update
REVNUM != svn update > /dev/null; svnversion
.else
REVNUM != svnversion
.endif
.else
REVNUM != cut -d= -f2 svnrev.xcconfig
.endif

CC      = clang
CFLAGS  = $(CDEFS) -DSVNREV=\"$(REVNUM)\" -Iinclude -Iinclude/compat -std=c11 -g0 -Ofast -mssse3 -Wno-parentheses -Wno-switch
LDFLAGS = -L/usr/local/lib -lm -lpthread -licuuc -lz
SOURCES = mrwlock.c summarise.c queryparse.c impact_build.c psettings_default.c vec.c dirichlet.c bit.c impact.c search.c \
          getlongopt.c poolalloc.c alloc.c objalloc.c okapi.c stem.c docmap.c index_querybuild.c mem.c psettings.c stack.c \
          pyramid.c heap.c hawkapi.c mlparse_wrap.c postings.c mlparse.c cosine.c reposset.c chash.c getmaxfsize.c lcrand.c \
          storagep.c pcosine.c rbtree.c mime.c staticalloc.c stop.c trec_eval.c error.c binsearch.c stop_default.c freemap.c \
          merge.c index.c signals.c btbucket.c str.c vocab.c btbulk.c remerge.c ioutil.c bucket.c makeindex.c iobtree.c utf8.c \
          fdset.c zpthread.c crc.c detectfilter.c gunzipfilter.c stream.c commandline.c
OBJECTS = $(SOURCES:.c=.o)
PRODUCT = zet

all: $(SOURCES) $(PRODUCT)

depend:
	$(CC) $(CFLAGS) -E -MM $(SOURCES) > .depend

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.core $(PRODUCT)

update: clean all

install: $(PRODUCT)
	strip -o /usr/local/bin/$(PRODUCT) $(PRODUCT)
