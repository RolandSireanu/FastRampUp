#include <iostream>
#include <vector>
#include <random>
#include <string>
using namespace std;

struct Person
{
    unsigned int age;
    string name;

};

vector<Person> v {{18,"Alexandru"}, {22, "Popescu"}, {22, "Ionescu"},
                  {14, "Gabriel"}, {71, "Tanase"}};


ostream& operator << (ostream& stream, const Person& p)
{
    return stream <<"Age : " << p.age << ", Name : " << p.name << endl;
}


namespace
{
    template<typename T>
    void printVector(const vector<T>& v)
    {
        for(const auto& e : v)
            cout << e << " ";
        cout <<endl;
    }  

    template<typename T>
    void shuffleVector(vector<T>& v)
    {
        auto rng = std::default_random_engine {};
        shuffle(std::begin(v), std::end(v), rng);
    } 

    void print()
    {
        cout << endl;
    }

    template<typename T, typename ...Args>
    void print(T arg, Args... args)
    {
        cout << arg << " ";
        print(args...);
    }


};

//Other runes :D 
// *_n , *_if, is_*_until, *_copy


int main()
{
    print("Before :");
    printVector(v);
    //keeps the relative order of element 
    //Popescu before Ionescu
    stable_sort(v.begin(), v.end(), [](const Person& arg, const Person& arg2){
        return arg.age < arg2.age;
    });
    print("After  : stable_sort ");
    printVector(v);

    bool result = is_sorted(v.begin(), v.end(), [](const Person& arg, const Person& arg2){
        return arg.age < arg2.age;
    });
    if(result)
        print("Sorted vector !");
    else
        print("Random vector ! ");


    return 0;
}
