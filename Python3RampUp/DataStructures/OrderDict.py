# Order dict remembers the insertion order 

import collections


ordDict = collections.OrderedDict({"firstElement":22 , "secondElement":0, "thirdElement":3})
print(ordDict)

ordDict["fourthElement"] = "none"
print(ordDict)
