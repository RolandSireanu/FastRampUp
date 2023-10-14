#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

//Descriptors used: pfdIn[0], pfdOut[1]
int pfdIn[2];
int pfdOut[2];

const int DATABASE_LENGTH = 27;
const char* database = "beauty\nlong\nhair\napple\n";


int main()
{
    char temp[100];
    int nrOfBytesRead = 0;
    pid_t pid;

    if(pipe(pfdIn)) { /*perror("Pipe creation error \n");*/ }
    if(pipe(pfdOut)) { /*perror("Pipe creation error \n");*/ }

    if((pid = fork()) == 0)
    {
        dup2(pfdIn[0], STDIN_FILENO);
        dup2(pfdOut[1], STDOUT_FILENO);
        close(pfdIn[0]);
        close(pfdIn[1]);
        close(pfdOut[0]);
        close(pfdOut[1]);
        execlp("sort", "sort", (char*)NULL);
    }

    close(pfdIn[0]);
    close(pfdOut[1]);

    //Write text to sort
    write(pfdIn[1], database, DATABASE_LENGTH);
    close(pfdIn[1]);


    while(1)
    {
        nrOfBytesRead = read(pfdOut[0], temp, sizeof(temp));
        if(nrOfBytesRead == 0)
            break;
        write(STDOUT_FILENO, temp, nrOfBytesRead);        
    }
    
    close(pfdOut[0]);
    waitpid(pid, NULL, 0);

    return 0;
}
