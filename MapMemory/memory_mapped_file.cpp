#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main()
{
    struct stat info;
    int fd = open("./myfile", O_RDWR | O_CREAT);
    fstat(fd, &info);

    printf("File size : %d\n", info.st_size);

    //Because MAP_PRIVATE changes will be seen just in the current process
    //If you want to modify the file for all the other processes , you should use MAP_SHARED
    // MAP_SHARED will share the mapped area to a child process.
    char* mmfile = (char*)mmap(NULL, info.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    printf("%s", mmfile);
    munmap((void*)mmfile, info.st_size);
    

    mmfile = (char*)mmap(NULL, info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    mmfile[0] = 'a';
    mmfile[2] = 'w';
    mmfile[4] = 'x';

    munmap((void*)mmfile, info.st_size);
    close(fd);



}