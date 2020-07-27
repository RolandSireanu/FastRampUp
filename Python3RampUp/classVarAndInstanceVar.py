# Class variable will be stored on class memory 
# Instance variables will be kept in objects memory 
# self.__class__.classVariable if you want to access class variable from within the object methods


class Dog:

    nrOfLegs = 4    #Class variable , shared by all objects

    def __init__(self,name):
        self.name = name;   #Instance variable , specific for each object 

    def __str__(self):
        return "Dog's name is " + self.name;


d1 = Dog("Labus")
print(d1)
print(Dog.nrOfLegs)
print(d1.name)

# ========================== Shadowing a class variable with an instance variable ========================== 

d1.nrOflegs = 5;    # A new instance variable is created with the same name as class variable 

print(Dog.nrOfLegs)
print(d1.nrOflegs)




