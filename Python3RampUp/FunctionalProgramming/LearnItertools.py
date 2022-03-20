import itertools
import ipdb

# ===================== Links ================
# https://docs.python.org/3.6/library/itertools.html#itertools-recipes
# https://realpython.com/python-itertools/

# The itertools module implements a number of iterator building blocks.
# Together they form an iterators algebra 
# Loosely speaking, this means that the functions in itertools “operate” on iterators to produce more complex iterators.
# For example zip function :

#  built-in zip() function, which takes any number of iterables as arguments and returns an iterator over tuples of their corresponding elements:
# Under the hood, the zip() function works, in essence, by calling iter() on each of its arguments, then advancing each iterator returned by iter() with next() and aggregating the results into tuples. The iterator returned by zip() iterates over these tuples
# Zip stops aggregating elements when the shortest iterable passed to its exhausted.
it = zip([1,2,3],["A","B","C"])
# print(next(it))


# Map functin is another “iterator operator” that, in its simplest form, applies a single-parameter function to each element of an iterable one element at a time:
print(list(map(lambda t : str(t[0])+str(t[1]), it)))

# print(sum(1,2,3,4,5))
print(sum((1,2,4,5)))
# ====== Create a data pipeline ========
print(list(map(sum , zip([1,2,3],[4,5,6]))))

#Grouper naive and smart approach

def naive_grouper(inputs, n):
    num_groups = len(inputs) // n
    return [tuple(inputs[i*n:(i+1)*n]) for i in range(num_groups)]

def better_grouper(inputs, n):
    #Create a list with n iterators of the same iterable
    iterators = [iter(inputs)] * n
    #zip(it1, it2 , ... , itn)
    #when next is called will output one value from each of n iterators
    #but because they are all referencing to the same list it will be just
    #a grouping of n list elements.
    
    #If len(inputs) is not divizible by n , 
    #we have a problem, last element are not processed
    # return zip(*iterators)
    return itertools.zip_longest(*iterators)


inputList = [1,2,3,4,5,6]
print([i for i in better_grouper(inputList, 4)])


# === Combinations ===
# You have three $20 dollar bills, five $10 dollar bills, two $5 dollar bills, and five $1 dollar bills. 
# How many ways can you make change for a $100 dollar bill?
bills = [20,20,20,10,10,10,10,10,5,5,1,1,1,1,1]
makes_100 = set()
for n in range(1, len(bills) + 1):
    for combination in itertools.combinations(bills, n):
        if sum(combination) == 100:
            makes_100.add(combination)
print(makes_100)


#How many ways are there to make change for a $100 bill using 
#any number of $50, $20, $10, $5, and $1 dollar bills?
bills = [50, 20, 10, 5, 1]
make_100 = set()
for n in range(1,101):
    for combination in itertools.combinations_with_replacement(bills, n):
        if(sum(combination) == 100):
            make_100.add(combination)
print("There are :"+str(len(make_100)) + " ways to make 100$")
    