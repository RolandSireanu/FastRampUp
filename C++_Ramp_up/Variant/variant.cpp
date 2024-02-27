#include <variant>
#include <vector>
#include <iostream>
using namespace std;

void f(int) { cout << " int " << std::endl; }
void f(char) { cout << " char " << std::endl; }
void f(double) { cout << " double " << std::endl; }



int main()
{
    vector<variant<int, char, double>> v = {1,'c',3.0};

    for(const auto& e : v)
    {
        std::visit([](auto&& arg){ f(arg); }, e);
    }

    // How does std::visit know which function overload to invoke?
        // #ifdef INSIGHTS_USE_TEMPLATE
        // template<>
        // inline /*constexpr */ void operator()<const int &>(const int & arg) const
        // {
        //   f(arg);
        // }
        // #endif
        
        
        // #ifdef INSIGHTS_USE_TEMPLATE
        // template<>
        // inline /*constexpr */ void operator()<const char &>(const char & arg) const
        // {
        //   f(arg);
        // }
        // #endif
        
        
        // #ifdef INSIGHTS_USE_TEMPLATE
        // template<>
        // inline /*constexpr */ void operator()<const double &>(const double & arg) const
        // {
        //   f(arg);
        // }
        // #endif
    // It generates a lambda overload for each type of the variant

}