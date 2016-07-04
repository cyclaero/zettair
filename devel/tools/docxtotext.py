#!/usr/bin/python

import sys

try:
    from xml.etree.cElementTree import XML
except ImportError:
    from xml.etree.ElementTree import XML

import zipfile

WORD_NAMESPACE = '{http://schemas.openxmlformats.org/wordprocessingml/2006/main}'
PARA = WORD_NAMESPACE + 'p'
TEXT = WORD_NAMESPACE + 't'

def docx2text(path):
    document = zipfile.ZipFile(path)
    xml_content = document.read('word/document.xml')
    document.close()
    tree = XML(xml_content)

    paragraphs = []
    for paragraph in tree.getiterator(PARA):
        texts = [node.text
                 for node in paragraph.getiterator(TEXT)
                 if node.text]
        if texts:
            paragraphs.append(''.join(texts))

    return '\n\n'.join(paragraphs)

try:
    print '<HTML><BODY>'
    print docx2text(str(sys.argv[1])).replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;').encode('ISO-8859-1', 'ignore')
    print '</BODY></HTML>'
except:
  sys.exit(1)

sys.exit(0)
