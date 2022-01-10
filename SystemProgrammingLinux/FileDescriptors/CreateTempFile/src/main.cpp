#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <unistd.h>



int main()
{
    char pathname[] = "/tmp/dataXXXXXXXXXXXX";
    char message[] = "Something is fishy !";
    //This will create and return fd to unique filename
    int fd = mkstemp(pathname);
    
    print(fd);
    write(fd, message, sizeof(message));
    print(pathname);
    close(fd);

    //Delete if nobody keeps a link to it
    unlink(pathname);

    return 0;
}