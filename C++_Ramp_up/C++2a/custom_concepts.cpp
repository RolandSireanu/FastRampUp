#include <concepts>

// What is a concept
// We can imagine a concept being a set of requirements for a type. 
// We pass the type to a concept at compile time, and the concept returns true if the type meets the requirements
// We pass the type as a template argument, and get a boolean back at compile time

// For a type to satisfy a concept, the statements within the requires expression must be valid for that type. 
// That does not mean the expression needs to evaluate to true.

template<typename T>
concept Integer = requires {
    std::integral<T>;       // This needs to be valid, not necessary true
};

template<typename T>
concept Integer = requires {
    requires std::integral<T>;       // Now this needs to be true
};


template<typename T>
concept MyIsIntegral = std::integral<T>;


// ======================= Functional requires syntax ====================

// In the above example, we’re asking the compiler to imagine x is an instance of our template type, T.
// We’re then asking it to determine whether x + x would be a valid statement in that scenario. 
// If this would be valid, then T satisfies our concept.
template<typename T>
concept Addable = requires (T arg){
    arg + arg;
};

template<typename T>
concept Arithmetic = requires (T arg) {
    arg + arg;
    arg - arg;
    arg * arg;
    arg / arg;
};

// Multiple template parameters
// When the concept has multiple parameters, substitution provides the value for the first parameter.
// This means that if we’re using a concept to constrain template parameters, 
// and that concept requires multiple arguments, we need to provide the additional arguments within the argument list of our template.
template<typename T1, typename T2>
concept Addable = requires (T1 arg1, T2 arg2) {
    arg1 + arg2;
};

template<Addable<float> T>
auto sum();


int main()
{

    return 0;
}