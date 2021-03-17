#Shallow copy = a new data structure object is instantiated but only the 
#               references are copied from the old one 
#Deep copy = new data structure and containing objects are instantiated

import copy 
original = [[0,1,2],[3,4,5]]
copyOfOriginal = copy.copy(original)
print(id(original) != id(copyOfOriginal))
print(id(original[0]) == id(copyOfOriginal[0]))
deepOfOriginal = copy.deepcopy(original)
print(id(deepOfOriginal[0]) != id(original[0]))