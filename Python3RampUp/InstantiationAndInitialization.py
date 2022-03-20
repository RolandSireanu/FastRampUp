# Online Python compiler (interpreter) to run Python online.
# Write Python 3 code in this online editor and run it.
#Python's instantiation process : 
    # instance creation
    # instance initialization
    
    
# However, object.__new__() still accepts and passes over extra arguments to .__init__() if your class doesn’t override .__new__(), as in the following variation of SomeClass:
class Animal:
    
    def __new__(cls, *args, **kwargs):
        newObject = super().__new__(cls)
        # print(dir(newObject))
        
a = Animal()



class Distance(float):
    
    def __new__(cls, value, unit):
        instance = super().__new__(cls, value)
        instance.unit = unit
        return instance

d = Distance(22.3, "km");

class Single:
    instance = None
    
    def __new__(cls, *args, **kwargs):
        if cls.instance == None:
            cls.instance = super().__new__(cls)
        return cls.instance
        
    
    def __init__(self):
        print("Init is evaluated ")
        
        
from operator import itemgetter

def named_tuple_factory(class_name, *fields):
    num_fields = len(fields)
    
    class NamedTuple(tuple):
        __slots__ = ()
        
        def __new__(cls, *args):
            if len(args) != num_fields:
                raise TypeError("error")
            cls.__name__ = class_name;
            
            for idx, fldName in enumerate(fields):
                setattr(cls, fldName, property(itemgetter(idx)))
            return super().__new__(cls,args)
            
        def __repr__(self):
            return f"""{class_name}({", ".join(repr(arg) for arg in self)})"""
    return NamedTuple
    
Point = named_tuple_factory("Point", "x", "y")
p = Point(2,3)
print(p.x)
            
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    
