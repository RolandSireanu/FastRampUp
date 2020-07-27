

class Component:

    classVariable = 0xFF;

    def __init__(self):
        print("Component constructor ! ")

    @classmethod
    def f1(cls):
        print(cls.classVariable)

    @staticmethod
    def f2():
        print("Static method ! ")




Component.f1();
Component.f2();




class Pizza:

    def __init__(self, ingredients):
        self.ingredients = ingredients;
    

    @classmethod
    def quatroFormagi(cls):
        return cls(["branza", "branza", "branza", "branza"]);

        
    def __repr__(self):
        ingr=""
        for s in self.ingredients:
            ingr = ingr + " " + s;
        return ingr;

p = Pizza.quatroFormagi();
print(p);
    

