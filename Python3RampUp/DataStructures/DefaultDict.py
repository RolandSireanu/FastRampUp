# If you try to read a undefined key-element pair , normally python would throw an error
# DefaultDict will create the element whenever you try to access it , using the functor provided
# in the DefaultDict constructor 

import collections

d = collections.defaultdict(int);

# This will create an element with key 'a' and value 0 due to 'int' in constructor
print(d["a"])
