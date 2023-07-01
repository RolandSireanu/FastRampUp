#include <iostream>
#include <arm_neon.h>
using namespace std;

int getMax(int* a, int* b, int length)
{
    for(int i{0}; i<length; i+=2)
    {
        int32x2_t temp = vld1_s32(a+i);
        int32x2_t temp2 = vld1_s32(b+i);
        int32x2_t result = vpmax_s32(temp, temp2);
        int32x2_t final = vpmax_s32(result, result);
        int max {vget_lane_s32(final, 0)};
    }
}


int main()
{
    int a[] {6,4,1,0,8,0};
    int b[] {9,2,11,3,8,0};
    std::cout << getMax(a, b, 6);

    return 0;
}