#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

static void sigcont_handler(int temp) 
{
    printf("temp = %d \n", temp);
    printf("Caught SIGUSR1 \n !");
}


int main()
{
    pid_t pid = getpid();
    printf("Current pid is %d\n", pid);

    if(signal(SIGUSR1, sigcont_handler) == SIG_ERR) 
    {
        fprintf(stderr, "Can't handle SIGUSR1 ! \n");
    }

    for (;;)
        pause ( );
    return 0;
}