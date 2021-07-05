#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator> 
using namespace std;

class Algorithm
{
    public:
        void templateMethod() 
        {
            initVector(16);
            splitNumbers();
            makeNegative();
            showVector();
        }

        void initVector(int length) 
        { 
            generate_n(back_inserter(v), length, [i{1}]() mutable { 
                int result = i * i;
                i++;
                return result;
            });            
        }

        void showVector() 
        {
            for(const auto& e : v)
                cout << e << endl;
        }


        virtual void makeNegative() 
        {
            for_each(v.begin(), v.end(), [](int& element){
                element = element * (-1);
            });
        }
        virtual void splitNumbers() = 0;
    protected:
        vector<int> v;
}; 

class ExtendedAlgorithm : public Algorithm 
{
    public:

        ExtendedAlgorithm() = default;
        void splitNumbers() 
        {
            for(auto& e : v) e = e / 2;
        }
};


int main()
{
    unique_ptr<Algorithm> algo = make_unique<ExtendedAlgorithm>();
    algo->templateMethod();

    return 0;
}
