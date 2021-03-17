#Mutable objects can be modified after instantiation , immutable objects can't.
#Object of built-in type: int,float,str,tuple,bool are imutable
#List , set , dict are mutable 
l1 = [1,2,3]
#List is mutable so we can change the state after creatin
l1[0] = 4

#Tuple is an imutable object , its state can't be change after creation
t = (1,2,3)
#t[0] = 4

#Tuple is imutable , but contains a mutable object and its state can be changed
t=([1,2,3],"aaa")
t[0][0]=0   #This works

def f(arg):
    print(id(arg))


print(id(l1))
f(l1)
print(id(t))
f(t)
i = 3
print(id(i))
f(i)

import copy 
original = [[0,1,2],[3,4,5]]
copyOfOriginal = copy.copy(original)
print(id(original) != id(copyOfOriginal))
print(id(original[0]) == id(copyOfOriginal[0]))
deepOfOriginal = copy.deepcopy(original)
print(id(deepOfOriginal[0]) != id(original[0]))