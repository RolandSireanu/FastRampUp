
# If two keys have the same hash value and are equals based on __eq__ bundle 
# than the key and the value will be overwritten like in example below 


class Car :

    def __eq__(self,arg1):
        return True;

    def __hash__(self):
        return 1 


c = Car()

print(hash(c))


d = {Car() : 22 , Car(): 33}

print(d)

