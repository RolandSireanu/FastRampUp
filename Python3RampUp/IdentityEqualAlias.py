#In python variables are not boxes , are rather labes
#A variable is just a referene to an object

#First list [1,2,3,4,5] object is allocated 
#Second l is bind to recently created object 
l = [1,2,3,4,5]

#alisL is just and alias for l 
#aliasL and l holds references to same list not copies
aliasL = l;

print(id(l) == id(aliasL))

print(id(3))
print(id(4))