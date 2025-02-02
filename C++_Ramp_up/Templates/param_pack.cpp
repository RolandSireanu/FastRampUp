#include <iostream>

// Parameter pack expansion
// In most cases, an expanded pattern is conceptually equivalent to a number of copies of the pattern equal to the size of the parameter pack.
// List of contexts where a parameter pack can be expanded:

// 1. In a function call expression, the pattern is the argument list of the call expression.
    // In this particular explame there are two packs "Args" and "args". These two needs to be the same size because they are expanded in pairs.
    template<typename T, typename ... Args>
    std::unique_ptr<T> my_make_unique(Args ...args)
    {
        return unique_ptr<T>(new T{std::forward<Args>(args)...});
    }
    // Expands to ======>
    // template<>
    // std::unique_ptr<O, std::default_delete<O> > my_make_unique<O, int, int>(int __args0, int __args1)
    // {
    //   return /*...*/(new O{std::forward<int>(__args0), std::forward<int>(__args1)}));
    // }

// 2. In base specifier list
    class Car{};
    class Vehicle{};

    template<typename ...Args>
    class Dacia : public Args ...
    {
    };
    // Expands to ======>
    // class Dacia : public Car, public Vehicle
    // {
    // };

// 3. In a template argument list
    template<typename ...Args>
    auto make_me_a_tuple(Args ...args)
    {
        return std::tuple<Args...>(args...);      
    }
    // Expands to ======>
    // template<>
    // std::tuple<int, double, char> make_me_a_tuple<int, double, char>(int __args0, double __args1, char __args2)
    // {
    // return std::tuple<int, double, char>(__args0, __args1, __args2);
    // }

// 4. Inside an operator
    template<typename T, std::size_t... idx>
    auto getTupleFromVector(const std::vector<T>& arg, std::index_sequence<idx...>)
    {
        return std::make_tuple(arg[idx]...);
    }

    template<typename T>
    auto getTupleFromVector(const std::vector<T>& arg)
    {
        return getTupleFromVector(arg, std::index_sequence<1,2,3>{});
    }
    // ======> Expands to
    // std::tuple<int, int, int> getTupleFromVector<int, 1, 2, 3>(const std::vector<int, std::allocator<int> > & arg, std::integer_sequence<unsigned long, 1, 2, 3>)
    // {
    // return std::make_tuple(arg.operator[](1UL), arg.operator[](2UL), arg.operator[](3UL));
    // }

// 5. Inside a "using" declaration
    template<typename ...Base>
    struct MyStruct :  Base... {
        MyStruct();
        using Base::f...;
    };
    // Expands to ======>
    // using Base_1::f;
    // using Base_2::f;


// Nice to know
    // 1. Get the number of parameters in a parameter pack with sizeof 
    template<typename ...Args>
    void foo(Args ...args)
    {
        std::cout << sizeof...(args) << std::endl;
    }


// Where a parameter pack can be captured
    // 1. Template paramter pack
    template<typename ...T> struct S1{};
    template<int ...I> struct S2{};

    // 2. Function parameter pack
    template<typename ...T> void f1(T ...t){}
    int f1(auto ...i){}


// =========================== Fold expressions ==============================

    template<typename TSet, typename ...Args>
    void multi_insert(TSet& aSet, Args&& ...args)
    {
        (aSet.insert(std::forward<Args>(args)),...);
    }
    // Expands to ====>
    // template<>
    // void multi_insert<std::set<int, std::less<int>, std::allocator<int> >, int, int>(std::set<int, std::less<int>, std::allocator<int> > & aSet, int && __args1, int && __args2)
    // {
    //   aSet.insert(std::forward<int>(__args1)) , aSet.insert(std::forward<int>(__args2));
    // }


int main()
{

    return 0;
}