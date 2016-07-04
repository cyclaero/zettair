#!/usr/local/bin/python

import sys, os, zipfile

try:
    from xml.etree.cElementTree import XML
except ImportError:
    from xml.etree.ElementTree import XML

PPTX_NAMESPACE = '{http://schemas.openxmlformats.org/drawingml/2006/main}'
PARA = PPTX_NAMESPACE + 'p'
TEXT = PPTX_NAMESPACE + 't'

def pptx2text(path):
    paragraphs = []
    document = zipfile.ZipFile(path)

    idx = 1
    while idx < 1000:
        slide = 'ppt/slides/slide'+str(idx)+'.xml'
        if slide in document.namelist():
            tree = XML(document.read(slide))

            for paragraph in tree.getiterator(PARA):
                texts = [node.text
                         for node in paragraph.getiterator(TEXT)
                         if node.text]
                if texts:
                    paragraphs.append(' '.join(texts))

        idx = idx + 1

    document.close()
    return '\n\n'.join(paragraphs)

try:
    print '<HTML><BODY>'
    print pptx2text(str(sys.argv[1])).replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;').encode('ISO-8859-1', 'ignore')
    print '</BODY></HTML>'
except:
  sys.exit(1)

sys.exit(0)
