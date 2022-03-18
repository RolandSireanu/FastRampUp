# type is the metaclass of all classes
# object is the parent of all classes
# a class is nothing more than a simple object 
Animal = type("Animal", (object,), {"name":"monkey"})
a = Animal()