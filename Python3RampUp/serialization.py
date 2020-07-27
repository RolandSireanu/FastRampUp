# used mainly for establishing a common data format for an object 
# You need to pack data tightly to serialize it to disk or to send
# it over the network
from struct import Struct 


s = Struct("fif");
packedStructure = s.pack(2.2,1,3.3)
print(packedStructure)

print(s.unpack(packedStructure))

