# Makefile for FreeBSD using LLVM/clang
#
# Usage examples:
#   make
#   make clean
#   make update
#   make install clean
#   make clean install CDEFS="-DDEBUG"

CC = clang

.if exists(.svn) || exists(../.svn) || exists(../../.svn) || exists(../../../.svn)
.ifmake update
REVNUM != svn update > /dev/null; svnversion
.else
REVNUM != svnversion
.endif
.else
REVNUM != cut -d= -f2 svnrev.xcconfig
.endif

.if $(MACHINE) == "i386" || $(MACHINE) == "amd64" || $(MACHINE) == "x86_64"
CFLAGS = $(CDEFS) -march=native -mssse3
.elif $(MACHINE) == "arm"
CFLAGS = $(CDEFS) -fsigned-char
.else
CFLAGS = $(CDEFS)
.endif

CFLAGS += -DSVNREV=\"$(REVNUM)\" -std=c11 -g0 -O3 -fstrict-aliasing -Wno-parentheses -Wno-switch -Iinclude -Iinclude/compat
LDFLAGS = -L/usr/local/lib -lm -lpthread -licuuc -lz
SOURCES = mrwlock.c summarise.c queryparse.c impact_build.c psettings_default.c vec.c dirichlet.c bit.c impact.c search.c \
          getlongopt.c poolalloc.c alloc.c objalloc.c okapi.c stem.c docmap.c index_querybuild.c mem.c psettings.c stack.c \
          pyramid.c heap.c hawkapi.c mlparse_wrap.c postings.c mlparse.c cosine.c reposset.c chash.c getmaxfsize.c lcrand.c \
          storagep.c pcosine.c rbtree.c mime.c staticalloc.c stop.c trec_eval.c error.c binsearch.c stop_default.c freemap.c \
          merge.c index.c signals.c btbucket.c str.c vocab.c btbulk.c remerge.c ioutil.c bucket.c makeindex.c iobtree.c crc.c \
          fdset.c zpthread.c detectfilter.c gunzipfilter.c stream.c utf8.c commandline.c
OBJECTS = $(SOURCES:.c=.o)
PRODUCT = zet

all: $(SOURCES) $(PRODUCT)

depend:
	$(CC) $(CFLAGS) -E -MM $(SOURCES) > .depend

$(PRODUCT): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.core $(PRODUCT)

update: clean all

install: $(PRODUCT)
	strip -o /usr/local/bin/$(PRODUCT) $(PRODUCT)
	cp ../tools/spider /usr/local/bin/spider
	cp ../tools/rtftotext.py /usr/local/bin/rtftotext.py
	cp ../tools/docxtotext.py /usr/local/bin/docxtotext.py
	cp ../tools/pptxtotext.py /usr/local/bin/pptxtotext.py
	cp ../tools/xlsxtotext.py /usr/local/bin/xlsxtotext.py
