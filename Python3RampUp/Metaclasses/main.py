
# In python classes are objects too. This is why we can handle
# them as we are handling objects.
# The following two constructions are equivalent
# This is the first construction. All this instructions are passed to a upper
# level class that probabbly using the "type" constructor will return you
# an object representing the class Student
# BY DEFAULT EVERY CLASS INHERITS FROM "TYPE" => class Student(type): 
class Student:
    def __init__(self):
        self.a = 5;
        self.b = 25;

    def addThemTogether(self):
        return self.a + self.b;
   
    
def addThemTogether(self):
    return self.a + self.b;

# This is the second construction
Student = type("Student", (), {"a" : 5, "b" : 25, "addThemTogether":addThemTogether});

s = Student();
print(s.addThemTogether());
