#include <iostream>

enum Colors
{
    RED = 0,
    YELLOW,
    GREEN
};
struct HwInterface
{
    void setSemaphore(Colors argColor){}
};
HwInterface hwInterface;

// The logic is combined with the hw actions
// In order to test it, you are going to need a mock for 
// setSemaphore. 
// So probabbly you won't unit test it.
void setTrafficLight(int32_t aWaitingPeople)
{
    if(aWaitingPeople > 10)                 // Logic
    {
        hwInterface.setSemaphore(GREEN);    // Hw action
    }
    else
    {
        hwInterface.setSemaphore(RED);      // Hw action
    }
}


// =========== A way better alternative ===============
// If you separate the logic from HW yoy can at lest test the logic.
// The main ideea is to separate the HW code (that needs mocking) from the logic code.
// The "getNextTrafficLight" can be easily unit tested 
Colors getNextTrafficLight(int32_t aWaitingPeople)
{
    return aWaitingPeople > 10 ? GREEN : RED;
}

void setTrafficLightImproved(int32_t aWaitingPeople)
{
    Colors c {getNextTrafficLight(aWaitingPeople)};
    hwInterface.setSemaphore(c);
}

// !!!!!! UNIT TESTS ENCOURAGE US TO KEEP THE CODE SIMPLER
// !!!!!! TRY TO MOCK AS LITTLE AS POSSIBLE

int main()
{
    Colors c{RED};
}