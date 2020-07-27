

# For using the keyword reserved in python , append _ and the and ex. class_
# _variable means private , for internal usage
# __variable means private and will be mangled by the interpreter in order NOT to be overriden by subclasses
# __var__ , this is called a Dunder , reserved word by pythoni
# _ , means temporary or insignificant 

class ComponentA:


    def __init__(self,class_):
        self.class_ = class_;
        self._number1 = 0
        self.__number2 = 1


class ComponentB(ComponentA):

    def __init__(self):
        self.__number2 = 10;

    def printMember(self):
        print(self.__number2);


c = ComponentA("Animal");
c2 = ComponentB();
print(dir(c))   
c2.printMember()


# THis will result in error because __number2 is mangled 
# print(c.__number2)

for _ in range(128):
    print("Temporary var")


l = [('a',1,1.2) , ('b',2,2.2)]

for _, _, float_ in l:
    print(float_)
