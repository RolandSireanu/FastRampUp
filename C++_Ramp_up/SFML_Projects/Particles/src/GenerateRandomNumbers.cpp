#include <GenerateRandomNumbers.hpp>

namespace RandomNumbers
{

    std::random_device rd;
    std::mt19937 mt(rd());

    unsigned int generate(size_t low, size_t high)
    {
        std::uniform_real_distribution<double> dist(static_cast<float>(low), static_cast<float>(high));
        return dist(mt);
    }

    unsigned int generate()
    {
        return generate(1, 11);
    }
};