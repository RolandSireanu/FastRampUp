#include <iostream>
#include <string>
#include <vector>

class Widget
{
    public:
        void p() &&         //Implementation for case when *this is a rvalue
        {
            std::cout << "Rvalue of this" << std::endl;
        }

        void p() &
        {
            std::cout << "Lvalue of this" << std::endl;
        }


};


// How function reference qualifiers are improving the code performance

class MyData
{

    public:
        std::vector<int>& data() &
        {
            std::cout << "Addr of v in MyData = " << &v << std::endl;
            return v;
        }

        std::vector<int>&& data() &&
        {
            return std::move(v);
        }


    private:
        std::vector<int> v;

};

MyData make_class()
{
    return MyData();
}



int main()
{

    Widget w;
    w.p();
    Widget().p();

    MyData md;
    //A tempo object MyData() is created , copied to vec2 , then destroyed
    auto vec = md.data();       //Creates a copy of v in vec

    std::cout << "Addr vec = " << &vec << std::endl;


    //We should have some option to specify that , when data() is invoked
    //from and rvalue , the result should be an rvalue
    // ===> Function reference qualifiers ! 

    //No copies are done , just moving    
    auto&& vec2 = make_class().data();
    vec2.push_back(0x22);

    


    return 0;
}
