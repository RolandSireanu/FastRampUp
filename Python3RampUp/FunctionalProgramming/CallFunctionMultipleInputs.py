import itertools

# def starmap(function, iterable):
#     # starmap(pow, [(2,5), (3,2), (10,3)]) --> 32 9 1000
#     for args in iterable:
#         yield function(*args)


class functor:
    
    def __init__(self):
        pass
    
    def __call__(self, x,y):
        return x* y;
        

for i in itertools.starmap(functor(), [(1,2),(4,9), (8,8)]):
    print(i)
    #2,36,64