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

// We are telling the compiler not to generate
// specialization for int type. By declaring
// it extern, the user guarantes that it is
// defined somewhere else in another translation
// unit
extern template class Matematica<int>;

#endif