#!/usr/local/bin/python

import sys, os, zipfile
from xml.etree.ElementTree import XML

XLSX_NAMESPACE = '{http://schemas.openxmlformats.org/spreadsheetml/2006/main}'
STIN  = XLSX_NAMESPACE + 'si'
TEXT  = XLSX_NAMESPACE + 't'
ROW   = XLSX_NAMESPACE + 'row'
CELL  = XLSX_NAMESPACE + 'c'
FUNCT = XLSX_NAMESPACE + 'f'
VALUE = XLSX_NAMESPACE + 'v'

def xlsx2text(path):
    document = zipfile.ZipFile(path)

    tree = XML(document.read('xl/sharedStrings.xml'))

    content = []
    for strings in tree.iter(STIN):
        texts = [node.text
                 for node in strings.iter(TEXT)
                 if node.text]
        if texts:
            content.append(''.join(texts))

    idx = 1
    while idx > 0:
        sheet = 'xl/worksheets/sheet'+str(idx)+'.xml'
        if sheet not in document.namelist():
            break

        tree = XML(document.read(sheet))
        for row in tree.iter(ROW):
            for cell in row.iter(CELL):
                functs = [node.text
                         for node in cell.iter(FUNCT)
                         if node.text]
                if functs:
                    values = [node.text
                             for node in cell.iter(VALUE)
                             if node.text]

                    content.append(''.join(functs))
                    if values:
                        content.append(''.join(values))

        idx = idx + 1

    document.close()
    return '\n'.join(content)


try:
    print '<HTML><BODY>'
    print xlsx2text(str(sys.argv[1])).replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;').encode('ISO-8859-1', 'ignore')
    print '</BODY></HTML>'
except:
    sys.exit(1)

sys.exit(0)
