# List comprehension
print([nr for nr in range(10)])

#Dictionary comprehension
print({nr:nr*nr for nr in range(8)})

#Set comprehension
print({evenNr for evenNr in range(32) if evenNr % 2 == 0})

#Generator comprehension
# Very similar with list comprehension. One difference between them
# is that generators don't allocate memory for the whole list.
# They generate each value one by one

for i in (nr for nr in range(32)):
    print(i)
    break;

print(next((nr for nr in range(32)), None))