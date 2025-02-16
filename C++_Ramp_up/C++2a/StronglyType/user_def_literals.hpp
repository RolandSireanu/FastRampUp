#ifndef USER_DEFINED_LITERALS
#define USER_UDEFINED_LITERALS

#include "types.hpp"

namespace user_defined_literals
{
    constexpr Port operator""_port(unsigned long long int aPort)
    {
        return {.mPort = aPort};
    }

    constexpr LoadFactor operator""_loadFactor(long double aLoadFactor)
    {
        return LoadFactor{.mLoadFactor = static_cast<float>(aLoadFactor)};
    }
}

#endif // USER_DEFINED_LITERALS