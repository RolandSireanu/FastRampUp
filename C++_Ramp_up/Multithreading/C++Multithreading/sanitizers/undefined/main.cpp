#include <stdlib.h>

// Sanitize for undefined behaviors:
//  Array subscript out of bounds, where the bounds can be statically determined
//  Bitwise shifts that are out of bounds for their data type
//  Dereferencing misaligned or null pointers
//  Signed integer overflow
//  Conversion to, from, or between floating-point types which would overflow the destination

int main(int argc, char **argv) {
  int k = 0x7fffffff;
  k += 0xfffffff;
  return 0;
}