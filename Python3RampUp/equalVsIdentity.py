
# Equal == compare the value 
# Identity "is" compare the object id 


l = [1,2,3]
a = l;

if(a == l):
    print("Equals");

if(a is l):
    print("Identical");

c = [1,2,3]

if(a == c):
    print("Equals")

if(a is c):
    print("Identical")
else:
    print("Not identical")


