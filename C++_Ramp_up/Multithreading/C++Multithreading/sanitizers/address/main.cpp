#include <stdlib.h>

// AddressSanitizer (aka ASan) is a memory error detector for C/C++. It finds:
//  Use after free (dangling pointer dereference)
//  Heap buffer overflow
//  Stack buffer overflow
//  Global buffer overflow
//  Use after return
//  Use after scope
//  Initialization order bugs
//  Memory leaks

int main() {
  char *x = (char*)malloc(10 * sizeof(char*));
  free(x);
  return x[5];
}