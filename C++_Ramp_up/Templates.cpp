#include <iostream>
#include <vector>

//Templates generate code at compilee time based on the code usage 
//They can have two types of arguments , type and value 
template<typename T , int i>
void prt(T arg)
{
    std::cout << i << std::endl;
}

//Templates support default initialization

template<typename T = float , int nr = 0>
void prtF()
{
    std::cout << nr << std::endl;
}
 
// ================================================================================== 

class layer_base 
{
    public:
        virtual ~layer_base() = default;
};

class conv_layer final : public layer_base
{};

class fc_layer final : public layer_base
{

};


template<typename T>
class network final
{
    static_assert(std::is_floating_point<T>::value, "Expecting floating point type ! ");

    public:
        ~network()
        {
            for(auto const l : layers)
            {
                delete l;
            }
        }

        template<typename TL>
        void addLayer(TL&& layer);


    private:
        std::vector<layer_base*> layers;
};


template<typename T>
template<typename TL>
void network<T>::addLayer(TL&& layer)
{
    static_assert(std::is_base_of<layer_base,TL>::value, "Provide a child of the base class ");

    layers.emplace_back(new TL(std::forward<TL>(layer)));
}

//==================================================================

template<int arg> 
constexpr int f()
{
    return arg;
}

//we could have done just decltype(T1() + T2()) , but in case of user defined types
//with complex constructors , declval can return an rvalue ref to this classes without calling the
//constructor
template<typename T1 , typename T2>
auto sum(const T1& arg1 , const T2& arg2) -> decltype(std::declval<T1>() + std::declval<T2>())
{
    return arg1 + arg2;
}

// =================================Specialization ============================

template<> 
double sum(const double& arg1, const double& arg2)
{
    return arg1 + arg2;
}

//Unspecialized types remain in the <...>
template<typename T1>
auto sum(const T1& arg1 , const int& arg2) -> decltype(std::declval<T1>() + std::declval<int>())
{
    return arg1+arg2;
}

// Class specialization , members can vary !!! 

template<typename T>
class GeneralClass 
{
    public:
        void method() { std::cout <<"GeneralClass :: method ! " << std::endl; }

};

template<>
class GeneralClass<float>
{
    public:
        float member = 0.001f;
};



int main()
{

    prt<int,99>(100);
    prtF();
    prtF<int,22>();

    network<float> net;
    net.addLayer(conv_layer());
    net.addLayer(fc_layer());

    std::cout << f<2>() << std::endl;
    constexpr int i = 9;
    std::cout << f<i>() << std::endl;
    static_assert(std::is_same<decltype(sum(std::declval<int>(), std::declval<double>())), double>::value,
        "Type error");

    sum(2,2);

    //Class specialization , different specialization are allowed to have different states and behaviour
    GeneralClass<int> gci;
    gci.method();
    // gci.member;  GeneralClass<int> has no "member"

    GeneralClass<float> gcf;
    //gcf.method();     GeneralClass<float> has no "method"
    gcf.member;


    return 0;
}

