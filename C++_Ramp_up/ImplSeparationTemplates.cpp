Caveat: It is not necessary to put the implementation in the header file, see the alternative solution at the end of this answer.

Anyway, the reason your code is failing is that, when instantiating a template, the compiler creates a new class with the given template argument. For example:

template<typename T>
struct Foo
{
    T bar;
    void doSomething(T param) {/* do stuff using T */}
};

// somewhere in a .cpp
Foo<int> f; 
When reading this line, the compiler will create a new class (let's call it FooInt), which is equivalent to the following:

struct FooInt
{
    int bar;
    void doSomething(int param) {/* do stuff using int */}
}
Consequently, the compiler needs to have access to the implementation of the methods, to instantiate them with the template argument (in this case int). If these implementations were not in the header, they wouldn't be accessible, and therefore the compiler wouldn't be able to instantiate the template.

A common solution to this is to write the template declaration in a header file, then implement the class in an implementation file (for example .tpp), and include this implementation file at the end of the header.

Foo.h

template <typename T>
struct Foo
{
    void doSomething(T param);
};

#include "Foo.tpp"
Foo.tpp

template <typename T>
void Foo<T>::doSomething(T param)
{
    //implementation
}
This way, implementation is still separated from declaration, but is accessible to the compiler.

Alternative solution
Another solution is to keep the implementation separated, and explicitly instantiate all the template instances you'll need:

Foo.h

// no implementation
template <typename T> struct Foo { ... };
Foo.cpp

// implementation of Foo's methods

// explicit instantiations
template class Foo<int>;
template class Foo<float>;
// You will only be able to use Foo with int or float
If my explanation isn't clear enough, you can have a look at the C++ Super-FAQ on this subject.
