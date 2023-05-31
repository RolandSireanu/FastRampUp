
# This is a generator template 
class EvenNumbers:

    def __init__(self, boundery):
        self.boundery = boundery;
        self.counter = -2;

    def __next__(self):
        self.counter += 2;        
        if self.counter >= self.boundery:
            raise StopIteration;
        return self.counter;

    def __iter__(self):
        return self;

e = EvenNumbers(30);
for i in e:
    print(i);
        

#This is the same generator but in a much lighter form
def evenNumber(boundery):
    counter = -2;
    while counter < boundery:
        counter += 2;
        yield counter;

for i in evenNumber(30):
    print(i);


# Let's check the benefits of a generator, in any of its two forms
# We are going to be comparing based on memory usage
import sys

def genPows(boundery):
    for i in range(boundery):
        yield i**2

LIMIT = 10000;

allThePowsInMemory = [nr**2 for nr in range(LIMIT)];

# for element in zip(genPows(LIMIT), allThePowsInMemory):
#     print(element);

# How many bytes are used by the object we passed in
print(sys.getsizeof(allThePowsInMemory))
print(sys.getsizeof(genPows));

# For the list : 85176Ba
# For the generator : 136B