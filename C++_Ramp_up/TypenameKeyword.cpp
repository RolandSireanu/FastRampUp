// Short answer: Whenever referring to a nested name that is a dependent name, i.e. nested inside a template instance with unknown parameter.

// Long answer: There are three tiers of entities in C++: values, types, and templates. 
// All of those can have names, and the name alone doesn't tell you which tier of entity it is. 
// Rather, the information about the nature of a name's entity must be inferred from the context.

class Container
{
    public:
        using value = int;
};

template<typename T>
void f(T)
{
    //Without typename value could be a static member variable of type T
    typename T::value variable;
}