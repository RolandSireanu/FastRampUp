#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// This example will use pipes for communication between two related processes
// Child processes will replace his stdout with the write side of the pipe
// printf in the read side of the parent process


int pfd[2];

int main()
{
    pid_t child1, child2;
    FILE* a;

    int v = fpathconf(pfd[0], _PC_PIPE_BUF);
    printf("Limit size for atomic writes in pipe buffer %d \n", v);

    if(pipe(pfd)) { perror("Pipe creation error \n"); }

    switch (fork())
    {
        case -1:
            perror("Error at process creation ! \n");
            break;
        case 0:
            //child process
            close(pfd[0]);  //Close read
            // Close STDOUT and copy open file table entry from pipe write to STDOUT
            // Every byte printed on the screen will go to parent process thorugh STDOUT new configuration
            dup2(pfd[1], STDOUT_FILENO);
            close(pfd[1]);

            //Send 4 bytes to parent process
            printf("%x%x%x%x", 7, 7, 8, 1);

            exit(0);
            break;
        
            //parrent
            
    }

    close(pfd[1]);  //Close write
    unsigned char sms[4] = {1,1,1,1};
    sleep(2);
    int nr = read(pfd[0], sms, 4);
    printf("Nr of bytes read %d \n", nr);
    for(int i = 0; i < nr; i++)
        std::cout << sms[i] << " " << std::endl;

    close(pfd[0]);
    exit(0);


    return 0;
}