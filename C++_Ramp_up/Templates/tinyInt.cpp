#include <iostream>
#include <utility>
#include <math.h>
#include <string>
using namespace std;

template<int nrOfBits>
class tiny_int {

    static_assert((nrOfBits >= 1 || nrOfBits <= 8), "tiny_int is expecting between 1 and 8 bits");

    public:
        using rep = uint8_t;

        tiny_int(rep value) {
            if (value > (pow(2,nrOfBits)-1)) {
                throw "Value can't be represented on " + to_string(nrOfBits);
            } 
            else
            {
                this->value = value;
            }
        }

    private:
        rep value;
};


int main()
{

    tiny_int nr = tiny_int<4>(16);

    return 0;
}