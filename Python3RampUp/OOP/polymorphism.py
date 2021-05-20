from abc import ABC, abstractmethod

class Base(ABC):

    @abstractmethod
    def whoAmI(self):
        pass

class Cat(Base):

    def __init__(self):
        print("Cat constructor !");

    def whoAmI(self):
        return "I am a cat !";

class Dog(Base):

    def __init__(self):
        print("Dog constructor !");
    
    def whoAmI(self):
        return "I am a dog !";

class Chicken(Base):

    def __init__(self):
        print("Chicken constructor !");

def polymorphismWithFunction(polyObject):
    print(polyObject.whoAmI());

if __name__ == "__main__":
    c = Cat();
    d = Dog();
    # k = Chicken();    //This will fail , can't instantiate abstract base class

    polymorphismWithFunction(c);
    polymorphismWithFunction(d);

    for obj in [c,d]:
        print(obj.whoAmI());

