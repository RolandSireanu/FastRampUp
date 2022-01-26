import sys

#Unpacking = assigning an iterable of values to a (tuple or a list) of variables
#in a single assignment.
#Packing = collecting several values in a single variable using the iterable
#unpacking operator "*"

#Tuple unpacking
#The following syntaxes are equivalent
(v1, v2, v3) = (1, 1.2, 'a')
v1, v2, v3 = (1, 1.2, 'a')
v1, v2, v3 = 1, 1.2, 'a'
print(v3)

#The tuple unpacking feature got so popular among Python developers that
#the syntax was extended to work with iterable object
#The iterable yields exactly one item per variable in the receiving tuple | list
#We can use any iterable on the right side of assignment operator
v1,v2,v3,v4 = "abcd"
print(v2)

v1,v2,v3,v4 = ["Got","so","popular","!"]
print(v4)

gen = (i for i in range(0,8,2))
v1,v2,v3,v4 = gen
print(v3)

v1,v2,v3,v4 = {"key1":1, "key2":2, "key3":3, "key4":4}
print(v4)
v1,v2,v3,v4 = {"key1":1, "key2":2, "key3":3, "key4":4}.values()
print(v4)

#Packing with operator "*"
#Iterable unpacking operator
*v, = 1,2,3,4
print(v)

a,*v = 1,2,3,4
print(v)

*v, a, b = [1,2,3,4]
print(v)

gen = (i**2 for i in range(5))
*values, = gen
print(values)

#Split the values of an iterable
l = [1,2,3,4,5,6,7,8]
header, body, last = l[0] , l[1:3], l[4:]
print(header)
print(last)

header, *body, last = l
print(body)

*a, b, c = range(5)
print(a)


#Dropping unneeded values
a, b, *_ = 1,2,0,0,0
print(_)


major, minor, *_ = sys.version_info
print(major)
print(minor)

#Merging several iterables into a final sequence. 
#This functionality works for lists, tuples, and sets. 
t = (1,2,3)
l = ['a', 'b', 'c']
s = {1.1, 2.2, 3.3}
string = "awsome"

print([*t, *l, *s, *range(5), *string])


#Unpacking dictionaries with ** operator
#Merging two dictionaries
d1 = {'a':1, 'b':2, 'c':3}
d2 = {1:2, 2:4, 3:8}
print({**d1, **d2})


for a,*rest in [(1,2,3),(4,5,6),(7,8,9)]:
    print(a)

#args will be a tuple, kwargs will be a dict
def smart(arg1, *args, **kwargs):
    print(arg1)
    print(args)
    print(kwargs)

print(" ======= ")
smart(1,"strArgument",2.2, lastArgument=0)

def testFunction(arg1, arg2):
    print(arg1, arg2)

#The operator * unpack [1,"A"] into positional arguments
testFunction(*[1,"A"])
#the ** operator unpacks dictionaries into arguments whose names match 
#the keys of the unpacked dictionary.
testFunction(**{"arg2":5, "arg1": 0.001})

#Call function with named arguments
testFunction(arg2 = 22, arg1= 21)


def smarter(requiredArg, *args, **kwargs):
    print(requiredArg, args, kwargs)

smarter("simple", *(1,'a',2.2), **{"one":1, "two":2})



# Iterable unpacking turns out to be a pretty useful and popular feature in Python. 
# This feature allows us to unpack an iterable into several variables. 
# On the other hand, packing consists of catching several values into one variable using the unpacking operator, *.