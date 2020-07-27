# Named tuple is use to create imutable classes 
# Named tuples like tuples are imutable , you can't change the attributes

from collections import namedtuple



House = namedtuple("House",["rooms","area"])
house = House(3,80)

# house.rooms=22

print(house)
print("===")
print(*house)


print(house._asdict())
