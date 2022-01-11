
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


