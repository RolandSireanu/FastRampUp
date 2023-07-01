#include <arm_neon.h>

int Sum(int32_t* array, int32_t length)
{
    int32_t sum{0};
    int32_t index{0};
    uintptr_t source {reinterpret_cast<uintptr_t>(array)};

    if((source % 32) != 0)
        return 0;

    for(; index<(length-1); index+=2)
    {
        int32x2_t temp = vld1_s32(array+index);
        sum += vaddv_s32(temp);
    }

    for(; index<length; ++index)
    {
        sum += array[index];
    }
}


int main()
{

    return 0;
}   