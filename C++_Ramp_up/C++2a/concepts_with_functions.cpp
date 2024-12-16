#include <iostream>

// Concepts are compile-time predicates which constrain types.


#define VERSION 4

template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;

#if VERSION == 1
//  1. Use requires clause between the template param lista nd the function return type
        template<typename T>
        requires Number<T>
        T add(T a, T b) { return a + b; }        

//      The drawback is that for each new function param you will need to introduce a new template and requirement on it
        template<typename T, typename U>
        requires Number<T> || Number<U>
        auto add(T a, U b) { return a + b; }

#elif VERSION == 2
//  2. Trailing requires clause
        template<typename T, typename U>
        auto add(T a, T b) requires Number<T> && Number<U> { return a + b; }

//      Still we have the drawback of scalability, each new function param of diff types
//      requires its own template parameter and requirement        

#elif VERSION == 3
//  3. Constrained template parameter
        template<Number T, Number U>
        auto add(T a, U b) { return a + b; }
//      Drawback is that you can't have complex constraints like constraint1 && constraint2

#elif VERSION == 4
//  4. Abbreviated function templates        
        auto add(Number auto a, Number auto b) { return a+b; }
//      Drawback is that you can't use complex expressions to articulate our constraints        
#endif

void push_element_in_container(auto& aContainer, auto& aElement)
requires std::convertible_to<decltype(aElement), typename decltype(aContainer)::value_type>
{
    if constexpr(requires {aContainer.push_back(aElement);})
        aContainer.push_back(aElement);
    else
        aContainer.insert(aElement);
}



int main()
{
    int a{3};
    add(a, 54.13f);
    add(a,a);
}