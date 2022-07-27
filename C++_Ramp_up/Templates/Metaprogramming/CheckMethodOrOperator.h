#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;


class no_container {};

template<class, class=void>
struct has_hash
    : std::false_type
{};

//How decltype with comma-separated list of expressions works ?
// It's an comma-separated list of expressions, the type is identical to the type of the last expression in the list. 
// It's usually used to verify that the first expression is valid (compilable, think SFINAE), 
// the second is used to specify that decltype should return in case the first expression is valid.

// => If the expression is valid, decltype(void()) will be used, hence the specialization is choosen
//rather than the generalization.
// => If the expression is invalid, the specialization fails !
template<class T>
struct has_hash<T, decltype(begin(declval<T>()), void())>
    : std::true_type
{};


void spec(false_type arg) { cout << "False type " << endl; }
void spec(true_type arg) { cout << " True type " << endl; }

int main()
{
    spec(has_hash<vector<int>>{});
    // spec(my_struct<int,void>{});
    return 0;
}