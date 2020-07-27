# Let's say you have a list with multiple references to it , and you want to clean all the elements
# You can't "del l" , all the references will be destroyed 
# You can't assign an empty list , all the references will be destroyed 
# You CAN use the sushi operator "[:]" to delete all the elements but keep the list intact 

l = [1,2,3,4,5]
refL = l;

del l[:] 

print(refL)


# If you want to change the list elements without changing the list object 

l[:] = [2,3,4]

print(l)
print(refL)

# Creating a shallow copy if existing list 

shallowCopyOfL = l[:]

print(shallowCopyOfL is l)
