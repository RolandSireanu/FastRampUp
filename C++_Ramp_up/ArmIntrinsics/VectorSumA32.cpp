#include <arm_neon.h>
#include <iostream>
#include "logger.hpp"

//First version of vector accumulation, nothing special here
auto Accumulate(int8_t* aInput, int32_t aLenght)
{
    int32_t lRet {0};
    int32_t counter {0};

    constexpr int32_t step {16};
    const int32_t boundery {aLenght / step};
    const int32_t rest {aLenght % step};

    for(int i{0}; i<boundery; ++i)
    {
        int8x16_t lIn = vld1q_s8(aInput + (i*step));
        int8x8_t lResult = vpadd_s8(vget_high_s8(lIn), vget_low_s8(lIn));
        int16x8_t lTemp = vmovl_s8(lResult);
        int16x4_t lTemp2 = vpadd_s16(vget_high_s16(lTemp), vget_low_s16(lTemp));
        int32x4_t lTemp3 = vmovl_s16(lTemp2);
        int32x2_t lTemp4 = vpadd_s32(vget_high_s32(lTemp3), vget_low_s32(lTemp3));
        lRet += (vget_lane_s32(lTemp4, 0) + vget_lane_s32(lTemp4, 1));
    }

    for(int i{0}; i<rest; i++)
    {
        lRet += (*(aInput + step + i));
    }

    return lRet;
}

//This is the improved version, that uses vpadal_s8 pairwise addition accumulation
auto AccumulateV2(int8_t* aInput, int32_t aLenght)
{
    int32_t lRet {0};
    int16x4_t lResult {0,0,0,0};
    constexpr int32_t step {16};
    const int32_t boundery {aLenght / step * step};

    for(int i{0}; i<boundery; i+=step)
    {
        int8x16_t lIn = vld1q_s8(aInput + i);

        lResult = vpadal_s8(lResult, vget_low_s8(lIn));
        lResult = vpadal_s8(lResult, vget_high_s8(lIn));
    }

    lRet += (vget_lane_s16(lResult, 0) + vget_lane_s16(lResult, 1) + vget_lane_s16(lResult, 2) + vget_lane_s16(lResult, 3));

    for(int i{boundery}; i<aLenght; ++i)
    {
        lRet += aInput[i];
    }

    return lRet;
}

//The fully optimized version with Multiple accumulations and loop peeling
int32_t AccumulateFullyOptimized(int8_t* aInput, int32_t aLength)
{
    int32_t lRet {0};
    int16x4_t lResult1 {0, 0, 0, 0};
    int16x4_t lResult2 {0, 0, 0, 0};
    constexpr int32_t step {32}; // We will process 32 bytes per iteration now
    const int32_t boundary {aLength / step * step};

    //Loop peeling, counting from step to step
    for(int i{0}; i<boundary; i+=step)
    {
        int8x16_t lIn1 = vld1q_s8(aInput + i);
        int8x16_t lIn2 = vld1q_s8(aInput + i + 16); // Process another 16 bytes

        lResult1 = vpadal_s8(lResult1, vget_low_s8(lIn1));
        lResult1 = vpadal_s8(lResult1, vget_high_s8(lIn1));
        lResult2 = vpadal_s8(lResult2, vget_low_s8(lIn2));
        lResult2 = vpadal_s8(lResult2, vget_high_s8(lIn2));
    }

    lResult1 = vadd_s16(lResult1, lResult2); // Combine the results
    lRet += (vget_lane_s16(lResult1, 0) + vget_lane_s16(lResult1, 1) + vget_lane_s16(lResult1, 2) + vget_lane_s16(lResult1, 3));

    // Loop peeling: process remaining bytes 16 at a time
    for(int i=boundary; i<aLength-15; i+=16)
    {
        int8x16_t lIn = vld1q_s8(aInput + i);
        lResult1 = vpadal_s8(lResult1, vget_low_s8(lIn));
        lResult1 = vpadal_s8(lResult1, vget_high_s8(lIn));
    }
    lRet += (vget_lane_s16(lResult1, 0) + vget_lane_s16(lResult1, 1) + vget_lane_s16(lResult1, 2) + vget_lane_s16(lResult1, 3));

    // Process remaining bytes one at a time
    for(int i=aLength-aLength%16; i<aLength; ++i)
    {
        lRet += aInput[i];
    }

    return lRet;
}


int main()
{
    int8_t in[] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    std::cout << AccumulateV2(in, 17) << std::endl;
    std::cout << AccumulateGPT(in, 17) << std::endl;

    return 0;
}
