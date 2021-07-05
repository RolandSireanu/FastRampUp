#ifndef GENERATE_RANDOM_NUMBERS_H
#include <random>
namespace RandomNumbers
{
    extern std::random_device rd;
    extern std::mt19937 mt;

    unsigned int generate(size_t low, size_t high);
    unsigned int generate();

};

#endif