
# __str__ used for user interaction , give a nice representation of the object
# __repr__ used mostly for developers , when you inspect a component in terminal this method will be called 
# if __str__ is not provided , the interpreter will fall back to __repr__


class ComponentA:

    def __init__(self):
        self.color = "Red";

    def __str__(self):
        return f"This is a {self.color} component";

    def __repr__(self):
        return f"class ComponentA , attrs : color , value : {self.color}"

c = ComponentA();
print(c)

