#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char* LOCK_FILE = "/tmp/lock";

int main()
{
    int fd;

    if(fork() == 0)
    {   //Child process
        
        while(1)
        {
            unlink(LOCK_FILE);
            while(fd = open(LOCK_FILE, O_WRONLY | O_EXCL | O_CREAT, 0) == -1 && errno == EEXIST)
            {
                printf("Child process is trying to lock the file .... \n");
                sleep(1);
            }
            printf("Child process has sucessfully locked the file ! \n");
            close(fd);
            unlink(LOCK_FILE);
            sleep(1);
        }
    }
    else
    {   //Parent process
        while(1)
        {
            unlink(LOCK_FILE);
            while(fd = open(LOCK_FILE, O_WRONLY | O_EXCL | O_CREAT, 0) == -1 && errno == EEXIST)
            {
                printf("Parent process is trying to lock the file .... \n");
                sleep(1);
            }
            printf("Parent process has sucessfully locked the file ! \n");
            close(fd);
            unlink(LOCK_FILE);
            sleep(1);
        }
    }


    return 0;
}