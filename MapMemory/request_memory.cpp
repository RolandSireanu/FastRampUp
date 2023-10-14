#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>




int main(int argc, char *argv[])
{
	//Request a page o memory fron the Operating system and map it into current process space
	void* ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	int* p = (int*)ptr;
	*p = 22;

	printf("\n%d \n", *p);

	printf("Pointer to mapped area %p\n", ptr);
}
