
#Merging and overwriting two dictionaries 
a = {"google.ro":234 , "facebook.com":1209}
b = {"google.ro":100 , "gmail.com":99}

print(a|b);
a|=b


#Type hints 
l : list[int] = [2,4,6,8]
lstr : list[str] = ["aa" , "bbb"]
print(l)
print(lstr)

#Remove prefix/sufix from string
eng = ["Eng.Gheorghe" , "Eng.Patru", "Bobita" , "Eng.Dorel"]
simplePeople = [e.removeprefix("Eng.") for e in eng]
print(simplePeople)


#Using decorators from list
import functools



def oddNumbers(f):
    @functools.wraps(f)
    def justOddNumbers(*args, **kwargs):
        l = f(*args, **kwargs);
        newL = [e for e in l if e % 2 == 0]
        return newL;
    return justOddNumbers

def evenNumbers(f):
    @functools.wraps(f)
    def justEvenNumbers(*args, **kwargs):
        l = f(*args, **kwargs);
        newL = [e for e in l if e % 2 != 0]
        return newL;
    return justEvenNumbers

DECORATORS = {"odd":oddNumbers, "even":evenNumbers};

@DECORATORS["odd"]
def getNumbers(boundery):
    return [i for i in range(boundery)]

#Decorator syntactic sugar
#print(oddNumbers(getNumbers)(50))
print(getNumbers(50))