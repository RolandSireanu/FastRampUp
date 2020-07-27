
# In order to test if an object is callable or not you can use "callable(object)"


class ComponentA:

    def __init__(self):
        print("Constructor ComponentA called ! ")

    def __call__(self,arg1):
        print(f"Object called with {arg1}")



c = ComponentA();
if(callable(c)):
    c(22)
