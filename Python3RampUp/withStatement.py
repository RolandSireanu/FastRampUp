#With "with" statement you can be sure that the resourse aquisition and release will be done
#  Implement your own with context manager : 
#   1) CLASS BASED
#   2) GENERATOR BASED


with open("file") as f :
    f.write("Something")

# THIS two pieces of code are the same 

try:
    f = open("file")
    f.write("Something")

finally:
    f.close()

#=========================== CLASS BASED IMPLEMENTATION =================================
#Write your own component with context manager "with" 
class ManagedFile:
    def __init__(self, name):
        self.name = name
    
    def __enter__(self):
        self.file = open(self.name, 'w')
        return self.file
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        if self.file:
            self.file.close()

#========== GENERATOR BASED IMPLEMENTATION ==============================================
from contextlib import contextmanager

#When the ManagedFile is called , it opens the file , return it and suspend the execution until the 
#application leaves the "with" context , after that it continues the execution and close the file 

@contextmanager
def ManagedFile(fileName):
    try:
        f=open(fileName);
        yield f;
    finally:
        f.close()

with ManagedFile("file") as file:
    file.write("Hello world !")


    
