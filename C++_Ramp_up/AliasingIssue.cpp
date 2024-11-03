#include <iostream>
#include <cstdint>

// Aliasing and strict aliasing rule
// One pointer is said to alias another pointer when both refer to the same location or object.
// Strict aliasing is an assumption, made by the C (or C++) compiler, that dereferencing pointers to objects of different types will never refer to the same memory location
// Pointers to different built in types do not alias:
//     int16_t* foo;
//     int32_t* bar;


// Disabling the -fno-strict-aliasing flag has a serious impact on performance, because compiler has to be very carefull when accessing memory, example:
// uniform->b has to be reloaded at every iteration, because the compiler doesn't know if values don't overlap b in memory.
typedef struct
{
    uint16_t a;
    uint16_t b;
    uint16_t c;
} Sample;
  
void test( uint32_t* values, Sample* uniform, uint64_t count )
{
    uint64_t i;
 
    for (i=0;i<count;i++)
    {
        values[i] += (uint32_t)uniform->b;
    }
}

// BAD example, this code breaks the strict aliasing rule
uint32_t swap_word(uint32_t arg)
{
    uint16_t* ptr {reinterpret_cast<uint16_t*>(&arg)};
    uint16_t low = ptr[0];
    uint16_t high = ptr[1];

    ptr[0] = high;
    ptr[1] = low;

    return arg;
}

// Solution is to use a union for doing this.
typedef union
{
    uint32_t u32;
    uint16_t u16[2];
}U32;
  
uint32_t swap_word_using_union( uint32_t arg )
{
    U32      in;
    uint16_t lo;
    uint16_t hi;
 
    in.u32    = arg;
    hi        = in.u16[0];
    lo        = in.u16[1];
    in.u16[0] = lo;
    in.u16[1] = hi;
 
    return (in.u32);
}

// Another solution is to make the cast through char*
// It is always presumed that a char* may refer to an alias of any object. It is therefore quite safe
uint32_t swap_word_with_char(uint32_t arg)
{
    char* const ptr = (char*)&arg;
    const char p1 = ptr[0];
    const char p2 = ptr[1];
    const char p3 = ptr[2];
    const char p4 = ptr[3];

    ptr[0] = p4;
    ptr[1] = p3;
    ptr[2] = p2;
    ptr[3] = p1;

    return arg;
}

int main() 
{
    std::cout << swap_word_using_union(0xFFFF0000) << std::endl;
    std::cout << swap_word_with_char(0xFFFF0000) << std::endl;
    return 0;
}