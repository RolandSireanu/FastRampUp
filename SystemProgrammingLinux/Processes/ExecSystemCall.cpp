#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// When exec is called, the data and text memory segments of the current process are
// replaced with the ones comming from the called executable.
// It replaces a process image with another process image
// The PCB remains the same (also the fdt)

// there is no new process;
// many attributes of the calling process remain unchanged (in
// particular, its PID).  All that execve() does is arrange for an
// existing process (the calling process) to execute a new program.

int main(int argc, char* argv[])
{
    if(fork() == 0)
        execlp("date", "date", (char*)NULL);
    
    printf("Hello world : \n");
    // if(fork() == 0)
    // {   //Child process



    // }

    return 0;
}