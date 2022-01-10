# Using two pipes for send/receive data to 'sort' executable
Sort will read from stdin until 0 is received. 
Parent process sends 0 to sort when the pipe is closed.