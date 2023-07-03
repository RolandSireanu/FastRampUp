#include "arm_neon.h"
#include "logger.hpp"


int32_t count(int8_t* in, int8_t threshold, int32_t aLength)
{
    constexpr int32_t step {16};
    int32_t lCounter {0};
    int8x16_t lThreshold = vdupq_n_s8(threshold);
    const int32_t boundary {aLength / step * step};
    
    for(int i{0}; i<boundary; i+=step)
    {
        int8x16_t lInput = vld1q_s8(in + i);
        uint8x16_t lResult = vcgeq_s8(lThreshold, lInput);
        
        uint16x8_t pair_sum = vpaddlq_u8(lResult);
        uint32x4_t pair_sum2 = vpaddlq_u16(pair_sum);
        uint16x4_t lo = vget_low_u16(pair_sum);
        uint16x4_t hi = vget_high_u16(pair_sum);
        lCounter += (vget_lane_u16(lo, 0) + vget_lane_u16(lo, 1) +
                     vget_lane_u16(lo, 2) + vget_lane_u16(lo, 3) +
                     vget_lane_u16(hi, 0) + vget_lane_u16(hi, 1) +
                     vget_lane_u16(hi, 2) + vget_lane_u16(hi, 3)) / 255;        
        
    }

    for(int i{boundary}; i<aLength; i++)
    {
        if(in[i] >= threshold)
            lCounter++;
    }
    
    
    return lCounter;
}


int main()
{
    int8_t input [] {2,4,6,8,1,3,4,7,2,4,6,8,1,3,4,7};
    std::cout << count(input, 5, 16) << std::endl;
    
    return 0;
}