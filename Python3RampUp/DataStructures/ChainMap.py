# ChainMap will consolidate multiple dictionaries and search after a key in all of them 

import collections 

d1 = {"a1":22 , "a2":11}
d2 = {"b1":33 , "b2":44}

cm = collections.ChainMap(d1,d2)

print(cm["b1"])
