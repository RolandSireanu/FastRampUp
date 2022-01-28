import os 
import PyPDF2
import ipdb
from pathlib import Path

currentPath = Path(os.getcwd()) if len(os.sys.argv) <= 2 else Path(os.sys.argv[2])

def findText(text, pdfPath):
    pdfFileObj = open(pdfPath, 'rb')
    pdfReader = PyPDF2.PdfFileReader(pdfFileObj)
    for page in range(0,pdfReader.numPages):
        pageObj = pdfReader.getPage(page)
        if text in pageObj.extractText():
            pdfFileObj.close();
            return True;
    pdfFileObj.close()
    return False


#Generator
pdfsGen = currentPath.glob("**/*.pdf")
gen = (pdfFile for pdfFile in pdfsGen if findText(os.sys.argv[1], pdfFile))

pdfFiles = [*gen]
print("Text has been found in " + str(len(pdfFiles)) + " pdf files")
print(pdfFiles)