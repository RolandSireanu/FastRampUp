
# Anonymus function have only ONE expression 
# Can't have a return statement , it is a default one 
# Use anonymus functions whenever you require a callable object (functor)


def firstOrder(f):
    f("Roland")


firstOrder(lambda message : print(message));


# ========================== Tuple example ===================== 

t = [(7,"adsa") , (2,"wqe") , (0,"sapte")]

print(sorted(t,key=lambda x : x[0]))

