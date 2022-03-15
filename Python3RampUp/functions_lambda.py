
# Anonymus function have only ONE expression 
# Can't have a return statement , it is a default one 
# Use anonymus functions whenever you require a callable object (functor)


def firstOrder(f):
    f("Roland")


firstOrder(lambda message : print(message));


# ========================== Tuple example ===================== 

t = [(7,"adsa") , (2,"wqe") , (0,"sapte")]

print(sorted(t,key=lambda x : x[0]))

# =================================================================================================

anonFunc1 = lambda x,y: True if x>y else False
anonFunc2 = lambda x,y: x>y
#anonFunc1 and anonFunc2 are equivalents , lambda just returns the result of expression

#multiple if else in the same lambda function, again lambda just evaluates the expression and returns the result
anonFunc3 = lambda x,y: x-y if x > y else (y-x if y > x else x)

if anonFunc1(5,2):
    print("5 is bigger than 2!")

print(anonFunc3(4,5))
print(anonFunc3(5,4))
print(anonFunc3(4,4))
