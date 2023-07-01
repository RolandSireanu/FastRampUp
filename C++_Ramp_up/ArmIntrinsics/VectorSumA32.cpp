#include <arm_neon.h>
#include <iostream>

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



int main()
{
    int8_t in[] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    std::cout << Accumulate(in, 17) << std::endl;

    return 0;
}
