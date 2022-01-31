import os 
import PyPDF2
import ipdb
from pathlib import Path
import itertools

def pdfFileGen(fileName):
    merger = PyPDF2.PdfFileMerger();
    try:
        while True:
            pdfFr = yield            
            merger.append(pdfFr)
    except GeneratorExit as e:
        merger.write(fileName)
        

out = pdfFileGen("./MergedFiles.pdf")
next(out)

if len(os.sys.argv) > 1 :
    for pdfFile in itertools.islice(os.sys.argv, 1, None):
        with open(pdfFile, 'rb') as tempPdf:
            pdfReader = PyPDF2.PdfFileReader(tempPdf);
            out.send(pdfReader)
else:
    print("Please specify pdf files as input arguments !")
            
out.close()

