from multiprocessing import context
import sqlite3 
import ipdb
from contextlib import contextmanager

class DataConnection:

    def __init__(self, arg_dbName):
        print("Data connection custroctor !");
        self.dbName = arg_dbName;

    def __enter__(self):
        """ acquire sql connection """
        self.conn = sqlite3.connect(self.dbName)
        return self.conn;

    # If any exception is raised in business logic code between enter and exit
    # the exception will be forwarded to __exit__
    # If the exception is handled in __exit__ return True if you want to
    # raise it further return False
    def __exit__(self, exc_type, exc_val, exc_tb):
        """ release sql connection """
        self.conn.close();
        if exc_val :
            return False

class FileContext:
    def __init__(self, arg_file, mode):
        self.file = arg_file
        self.mode = mode

    def __enter__(self):
        self.descriptor = open(self.file, self.mode);
        return self.descriptor

    def __exit__(self,  exc_type, exc_val, exc_tb):
        self.descriptor.close()
        if exc_val:
            return False

# ============== Same functionality but with context manager ===============
@contextmanager
def DataConnectionGen(dbName):
    try:
        conn = sqlite3.connect(dbName);
        yield conn;
    except AssertionError:
        print("We had an error")
    finally:
        print("Closing file!")
        conn.close()

@contextmanager
def fileContext(arg_file):
    try:
        descriptor = open(arg_file, "rw")
        yield descriptor
    except OSError:
        print("OSError")
    finally:        
        descriptor.close()




if __name__ == "__main__":
    dbName = "test.db";
    secondDbName = "test2.db"
    # temp = DataConnection(dbName)
    # conn = temp.__enter__();
    with DataConnection(dbName) as conn:
        cursor = conn.cursor()
    # temp.__exit__()

    # conn = DataConnectionGen(secondDbName)
    with DataConnectionGen(secondDbName) as conn:
        assert(1 == 2)
        cursor = conn.cursor()
    # resume execution next(conn)

    with FileContext("source", 'r') as source:
        with FileContext("destination", 'w') as dest:
            dest.write(source.read())
            