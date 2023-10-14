# Parent and child process , same entry in OFT (Open File Table)
Parent and child process reading from the same OFT entry.
Same read pointer is changed by both processes , so each one will start reading 
from where the previous one remains.