#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>

const char* sem_name = "Sagului";

 int main()
 {
     sem_t* sem = sem_open(sem_name, O_CREAT, 0600, 0);
     if(sem == SEM_FAILED)
        perror("Error at sem creation ! \n");
    
    unsigned int* arr = (unsigned int*)mmap(NULL, 32, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    

     if(fork() == 0)
     {
         //child process 
         sem_t* child_sem = sem_open(sem_name, O_CREAT, 0600, 0);
         printf("Child is working ... ! \n");
         arr[0] = 1;
         arr[1] = 2;
         arr[2] = 3;
         sleep(5);
         printf("Child finished working ! \n");
         sem_post(child_sem);
     }
     else
     {
         printf("Parent waiting for child ... \n");
        if(sem_wait(sem) < 0)
            perror("Error at sem_wait in parent \n ");
        
        printf("[Parent] Child is ready ! \n");
        printf("\n %d, %d, %d \n", arr[0], arr[1], arr[2]);

        if (sem_close(sem) != 0){
            perror("Parent  : [sem_close] Failed\n"); 
        }
        if (sem_unlink(sem_name) < 0){
            printf("Parent  : [sem_unlink] Failed\n");
        }
     }

     return 0;
 }