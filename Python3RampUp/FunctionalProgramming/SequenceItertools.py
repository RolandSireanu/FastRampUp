from ast import operator
import itertools as it
from threading import currentThread

counter = it.count(step=2)
print([next(counter) for i in range(5)])
repeter = it.repeat(5);
print([next(repeter) for i in range(5)])
cycle = it.cycle([-1,0,1])
print([next(cycle) for i in range(6)])

#add(3, 3) = add(add(1, 2), 3) = 6
print(list(it.accumulate([1,2,3], lambda x,y: x+y)))

#return (2,'w') , (2,'x') etc
print(list(it.product([2,5],['w','x'])))

#Create any number of independent iterators
it1, it2 = it.tee([1,2,3],2)
for i in [*it1, *it2]:
    print(i)


print(list(it.islice([1,2,3,4,5,6,7,8], 0,6,2)))
print(list(it.islice([1,2,3,4,5,6,7,8], 4)))    #from begining to index 4
print(list(it.islice([1,2,3,4,5,6,7,8], 5, None)))  # from index 5 to the end


for i in it.chain([1,2,3],[4,5,6]):
    print(i)

#Cut a deck of cards into half
#Without slicing (this would implie additional memory consumption)
def cutDeck(deck, n):
    d1, d2 = it.tee(deck,2)
    firstHalf = it.islice(d1, n)
    secondHalf = it.islice(d2, n, None)
    return it.chain(secondHalf, firstHalf)

deckOfCards = [i for i in range(26)];
print(list(cutDeck(deckOfCards, 13)))

def deal(deck, num_hands=2, hand_size=5):
    #Create one iterator for each caard in the hand
    iters = [iter(deck)] * hand_size

    #Build a generator that returns the first num_hands cards and consum it
    #Second iterator will start from where the first one finished
    # (0,1) , (2,3) , (4,5) num_hand x 
    gen = (tuple(it.islice(currentIt, num_hands)) for currentIt in iters)

    #unpack the generator and zip it 
    # prints (0,2,4,6,8) and (1,3,5,7,9)
    for g in zip(*gen):
        print(g)

deal(deckOfCards)