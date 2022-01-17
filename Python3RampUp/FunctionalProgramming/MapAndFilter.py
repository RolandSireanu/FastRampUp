l1 = ['a', 'b', 'c', 'd']
l2 = [1 , 2 , 3, 4]

def isEven(arg):
    if int(arg[1]) % 2 == 0:
        return True
    else:
        return False

#Apply function on every pair of inputs and returns an iterator
#to results.
it = (map(lambda x,y: x+str(y), l1, l2))

#Create a new list just with the elements that have been approved
#by predicate "isEven"
print(list(filter(isEven, it)))

