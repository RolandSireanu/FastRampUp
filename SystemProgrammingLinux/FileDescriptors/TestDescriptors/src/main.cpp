#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char* target_file = "/tmp/file";

// Parent process read 3 bytes, child will start reading 2 bytes from offset 3 .
// Parent will read again, 2 bytes from offset 5

int main()
{
    int fd = open(target_file, O_RDONLY, 0);
    unsigned char buffer[10];

    read(fd, buffer, 3);
    std::cout << buffer[0] << " " << buffer[1] << " " << buffer[2] << std::endl;

    if(fork() == 0)
    {   //Child process
        read(fd, buffer, 2);
        std::cout << buffer[0] << " " << buffer[1] << " " << std::endl;
        exit(0);
        
    }
    else
    {   //Parent process
        sleep(5);
        read(fd, buffer, 2);
        std::cout << buffer[0] << " " << buffer[1] << " " << std::endl;
    }

    close(fd);

    return 0;
}