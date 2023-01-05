#include <vector>
#include <array>
#include <string>
#include <iostream>
using namespace std;

constexpr array<unsigned int, 4> generateMemAreas(unsigned int base)
{
    constexpr int len = 4;
    array<unsigned int, len> r = {0};

    for(int i=0; i<len; i++)
    {
        r[i] = base | (i<<i);
    }

    return r;
}


struct Gpio
{
    enum IOFUNCTION : unsigned int { INPUT=0, OUTPUT=1} iofunction;
  	enum IOSPEED : unsigned int { LOW=0, MEDIUM=1, HIGH=2, EXTREME=5} iospeed;
    uint32_t alternateFunction;
};


int main()
{
    Gpio g;
    g.iofunction =  Gpio::INPUT;
	g.iospeed = Gpio::LOW;

    static constexpr array<unsigned int, 4> lMemAddrs = generateMemAreas(0x70000000);
    cout << lMemAddrs[1] << endl;


}
