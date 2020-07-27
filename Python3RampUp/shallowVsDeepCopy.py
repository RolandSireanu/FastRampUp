import copy

# Shallow copy (1 level copy ) just create a new DS (list , dict etc) and reference the original elements without creating new ones 
# Deep copy is a recursive copy , will create new DS and new objects 
# Objects can control how they are copied by using the __copy__ and __deepcopy__ dunders
# On primitive types there is no difference between shallow & deep copy 


l = [[1,2,3], [4,5,6], [7,8,9]]
shallowCopy = list(l);

# The lists are different , now identical
print(id(shallowCopy))
print(id(l))

# But the elements are referencing to the same objects 
print(id(shallowCopy[0]))
print(id(l[0]))


# If I change a common object , the change will be reflected in both lists
l[0][0] = 8
print(shallowCopy)


# ========================== Creating deep copies =========================== 
deepCopy = copy.deepcopy(l);
print(id(deepCopy))
print(id(l))

print(id(deepCopy[0]))
print(id(l[0]))

# Shallow copy has nothing in common with l




