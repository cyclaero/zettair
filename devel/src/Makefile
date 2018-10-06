# Makefile for the Zettair tools on FreeBSD using LLVM/clang
#
# Created by Dr. Rolf Jansen on 2018-06-11.
# Copyright © 2018. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
# OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
# IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
# THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


CC = clang

.ifmake debug
CFLAGS = $(CDEFS) -g -O0
STRIP  =
.else
CFLAGS = $(CDEFS) -g0 -O3
STRIP  = -s
.endif

.if $(MACHINE) == "i386" || $(MACHINE) == "amd64" || $(MACHINE) == "x86_64"
CFLAGS += -march=native -mssse3
.elif $(MACHINE) == "arm"
CFLAGS += -fsigned-char
.endif

CFLAGS += -std=gnu11 -fstrict-aliasing -Wno-parentheses -Wno-switch -I../include -I../include/compat
LDFLAGS = -L/usr/local/lib -lm -lpthread -lz
SOURCES = mrwlock.c summarise.c queryparse.c impact_build.c psettings_default.c vec.c dirichlet.c bit.c impact.c search.c \
          getlongopt.c poolalloc.c alloc.c objalloc.c okapi.c stem.c docmap.c index_querybuild.c mem.c psettings.c stack.c \
          pyramid.c heap.c hawkapi.c mlparse_wrap.c postings.c mlparse.c cosine.c reposset.c chash.c getmaxfsize.c lcrand.c \
          storagep.c pcosine.c rbtree.c mime.c staticalloc.c stop.c trec_eval.c error.c binsearch.c stop_default.c freemap.c \
          merge.c index.c signals.c btbucket.c str.c vocab.c btbulk.c remerge.c ioutil.c bucket.c makeindex.c iobtree.c crc.c \
          fdset.c zpthread.c detectfilter.c gunzipfilter.c stream.c commandline.c
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
	rm -f *.o $(PRODUCT)

debug: all

update: clean all

install: $(PRODUCT)
	install $(STRIP) $(PRODUCT) /usr/local/bin/
	cp ../Spider/spider /usr/local/bin/spider
	cp ../Spider/rtftotext.py /usr/local/bin/rtftotext.py
	cp ../Spider/docxtotext.py /usr/local/bin/docxtotext.py
	cp ../Spider/pptxtotext.py /usr/local/bin/pptxtotext.py
	cp ../Spider/xlsxtotext.py /usr/local/bin/xlsxtotext.py
