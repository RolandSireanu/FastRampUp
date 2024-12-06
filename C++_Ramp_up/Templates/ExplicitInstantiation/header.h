#ifndef HEADER_H
#define HEADER_H

template<typename T>
class Matematica
{
public:
    auto add(T lhs, T rhs) -> decltype(T() + T())
    {
        return lhs + rhs;
    }
};

extern template class Matematica<int>;

#endif