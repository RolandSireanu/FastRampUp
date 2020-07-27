from abc import ABCMeta , abstractmethod

class BaseClass(metaclass=ABCMeta):

    def __init__(self):
        print("BaseClass constructor called !")

    @abstractmethod()
    def baseMethod(self):
        pass


class DerivedClass(BaseClass):

    def __init__(self):
        print("Derived class constructor called ! ")

    
d = DerivedClass()

