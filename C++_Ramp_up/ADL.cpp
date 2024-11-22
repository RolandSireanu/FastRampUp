//ADL = Argument dependent lookup

#include <vector>
#include <iostream>

std::vector<int> v{1,2,3,4,5};

int main()
{
    // Why does it compile?
    // The "begin()" doesn't exist in the global namespace
    // It is declared/defined in the std namespace, how it is found?
    // ADL comes into play and searches in the namespace where the type of argument is defined.
    // "v" is a vector, defined in std, compiler will search for "begin()" function in std namespace.
    auto temp = begin(v);

    // The same situation for insetion operator "<<"
    // "cout" defined in the std, "<<" defined in std, compiler finds << in std based on the cout object type
    std::cout << "Hello world" << std::endl;

    

    return 0;
}