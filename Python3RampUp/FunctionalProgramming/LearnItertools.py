#  built-in zip() function, which takes any number of iterables as arguments and returns an iterator over tuples of their corresponding elements:
# Under the hood, the zip() function works, in essence, by calling iter() on each of its arguments, then advancing each iterator returned by iter() with next() and aggregating the results into tuples. The iterator returned by zip() iterates over these tuples
it = zip([1,2,3],["A","B","C"])
# print(next(it))


# Map functin is another “iterator operator” that, in its simplest form, applies a single-parameter function to each element of an iterable one element at a time:
print(list(map(lambda t : str(t[0])+str(t[1]), it)))

# print(sum(1,2,3,4,5))
print(sum((1,2,4,5))
# ====== Create a data pipeline ========
print(list(map(sum , zip([1,2,3],[4,5,6]))))