
# "with v" means v.__enter__()
# "with v as f" means f = f.__enter__()

class Component :

    def __init__(self, name):
        print("Constructor called ! ")
        self.fileName = name;

    def __enter__(self):
        self.fileDescriptor = open(self.fileName,"w");
        return self.fileDescriptor;

    def __exit__(self, exc_type, exc_val, exc_tb):
        if(self.fileDescriptor):
            self.fileDescriptor.close()


# c = Component("log")
# f = c.__enter__();
with Component("log") as f:
    f.write("Blablabla");
# c.__exit__()



class Indenter:

    def __init__(self):
        self.nrOfIndents = -1; 
        print("Constructor called !")
    
    def print(self,message):
        temp=""
        for i in range(self.nrOfIndents):
            temp += "\t";
        print(temp+message);


    def __enter__(self):
        print("DEBUG : __enter__ called by {}".format(self))
        self.nrOfIndents = self.nrOfIndents + 1;
        return self;
        
    def __exit__(self, exc_type, exc_val, exc_tb):
        return None;


with Indenter() as ind: 
    ind.print("Hello");
    #ind = ind.__enter__()
    with ind as ind:
        ind.print("World")
        #ind.__enter__()
        with ind:
            ind.print("Far away")


# =========== Context manager with contextlib ===============

from contextlib import contextmanager

@contextmanager
def openFileAt(path):
    try:
        f = open(path, 'r');
        yield f;
    except OSError:
        print("We have an os error");
    finally:
        print("Closing file");
        f.close();

with openFileAt("./GIL") as myFile :
    firstline = myFile.readline();
    print(firstline);







