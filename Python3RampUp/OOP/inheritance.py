
#super() can also take two parameters: the first is the subclass, and the second parameter is an object that is an instance of that subclass.

class Base:

    def __init__(self, value):
        print("Base constructor !")
        self.memberFromBase = value;

    def whoAmI(self):
        return "I am Base class "

class Derived(Base):

    def __init__(self, v):
        print("Derived constructor !")
        #super(Derived, self) it is equivalent to super()
        #This causes super() to start searching for a matching method called __init__
        #one level above "Derived" class in the instance hierarchy
        super(Derived, self).__init__(v)

    def test(self):
	    return self.memberFromBase;


d = Derived(22)
print(d.whoAmI())
print(d.test())

# Multiple inheritance and the diamond problem 

class Parent1:
    def howToTalk(self):
        print("Talk like parent 1")

class Parent2:
    name = "John"
    def howToTalk(self):
        print("Talk like parent 2")


class Toddler(Parent1, Parent2):
    def __init__(self):
        pass

t = Toddler();

#Diamon problem = the toddler doesn't know how to talk, like parent1 or parent2 
#Python resolves this by MRO (method resolution order), by order of classes in inheritance list
t.howToTalk()   #"Talk like parent 1"

#[ The MRO for Toddler class is = Toddler, Parent1, Parent2, Object]
print(Toddler.__mro__)

# This should look for "name" variable in MRO order => Parent2.name
# should gets printed
print(t.name)

# Access members from parent classes
print(super(Toddler, t).name)