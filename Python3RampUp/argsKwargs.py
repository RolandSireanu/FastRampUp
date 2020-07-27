

# *args will take the positional params in a tuple
# **kwargs will take keyword arguments in dictionary 

def f(arg1 , *args , **kwargs):
    print(arg1)
    print(args);
    print(kwargs)

f(1 , "a","b",car="alabala")


# ================== Function Argument Unpacking =====================

t = (2,4,7);

def f2(a,b,c):
    print(a+b+c)

f2(*t)

# ================ Dictionary unpacking in function arguments ========

d = {"a":23, "b":"A", "c":1.25}

def f3(a, b, c):
    print(a)
    print(b)
    print(c)

f3(**d)


# Puting an * in front of an iterable in a function call will unpack it and
# send the values to function argumetns 
# It works even for generator expressions , * will consume all the elements 
print("=======================================")
genExpr = (x for x in range(2,5))
f2(*genExpr)

