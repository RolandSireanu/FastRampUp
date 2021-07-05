#include <iostream>
#include <vector>
#include <stack>


//Adapter pattern 
//std::string doesn't have a constructor for conversion between numbers and string
//Through composition , we extend the string class with additional features.
//Our implementation is an adapter to string class
class string final {

    public:
        string(const int arg):impl{ std::to_string(arg) } {}
        string(const double arg):impl{ std::to_string(arg) } {}
        string(const char c):impl{ c } {}
    
        friend std::ostream& operator<<(std::ostream& os, const string& s); 

        template<typename T>
        T to();


    private:
        std::string impl;
};

std::ostream& operator<<(std::ostream& os, const string& s)
{
    return os << s.impl;
}

template<>
inline float string::to<float>() {
    return std::stof(impl);
}




int main()
{
    
    //std::stack is an adapter from std 
    //Underneath is using the vector data structure to implement stack operations
    std::stack<int , std::vector<int> > stck;

    string s(34);
    std::cout << s.to<float>() << std::endl;
    std::cout << s << std::endl;


    return 0;
}
