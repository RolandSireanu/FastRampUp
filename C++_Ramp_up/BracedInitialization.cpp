#include <iostream>
#include <vector>
#include <atomic>


//The 3 types of initializers 
int x (2);
int y = 2;
int z {2};



class Widget
{
    public:
        Widget() = default;
        Widget(const Widget& w) { std::cout <<"Copy constructor ! " << std::endl;}
        Widget& operator=(Widget& w) { std::cout <<"Copy operator = \n"; return w;}        


};
Widget w1;      
Widget w2 = w1;     //Copy constructor called

//================================== Braced initialization =========================
//In C++98 was no way to express that an STL containers should be created holding
//a set of particular values. => "Uniform initialization" ideea was introduced 
//implemented as "braced initialization" .
std::vector<double> v{2.2, 1.2, 3.2};

class C
{
    public:
        C(){}
        C(int a , int b){}
        C(std::initializer_list<int> a){ std::cout <<"Constructor initializer_list\n";}

    private:
    int member {22};   // This is fine ! 
    // int member(22) ; This is not allowed
};

std::atomic<int> ati{0};        //This is fine
// std::atomic<int> ati = 0;    Not allowed ! 

//Braced initialization prohibits implicit narrowing conversions among built-in types
//If the value of an expr in braced initialization isn't guaranteed to be expressible
//by the type of the object beeing initialized , the code will not compile.

//int var {2.2+3.2};
int var = 2.2+3.3;      //This compiles , this type of initialization doesn't check 
                        //for narrowing conversions because would break too much legacy
                        // code. 


//Braced initialization is imune to c++'s most vexing parse. Declaring a functin
//when you want to call a constructor with 0 arguments. 
//Type var();   this will declare a function 
C obj{};          //this will call the C constructor without args


//During constructor overload resolution, braced initializers are matched to
//std::initializer_list parameters if at all possible, even if other construc‐
//tors offer seemingly better matches

C smallObject {2,3};    //Now , this will call the initializer_list constructor.
                        //Before initializer_list constructor was declared , that expres would
                        //have called the 2 params constructor C(int,int).

int main()
{
    w1 = w2;       //Copy operator called
    std::vector<double> BigVectorSize(1024,2.32);
    return 0;
}