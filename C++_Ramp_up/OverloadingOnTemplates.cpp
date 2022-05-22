#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <string.h>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <memory>
#include <type_traits>
using namespace std;

// ====================== Overloading on templates ===================

vector<string> v;

template<typename T>
void function_1(T&& arg)
{
    v.emplace_back(forward<T>(arg));
}


void function_1(int arg)
{
    v.emplace_back(to_string(arg));
}

// ================= SOLUTION =================================================================
// It is not realistic to write an overload for each type function_1 could receive
// Solution: TYPE DISPATCHING + TYPE_TRAITS

//For integral type
template<typename T>
void function_2_pimp(T&& arg, true_type)
{
    v.emplace_back(to_string(arg));
}


//Overload for all other types but not integral
template<typename T>
void function_2_pimp(T&& arg, false_type)
{
    v.emplace_back(forward<T>(arg));
}

template<typename T>
void function_2(T&& arg)
{
    // std::is_integral_type<T>::type
    function_2_pimp(forward<T>(arg), std::is_integral<typename std::remove_reference<T>::type>());
}



int main ()
{
    function_1(string{"Hello World"});
    function_1("World Hello");
    function_1(221);

    cout << v[0] << endl;
    cout << v[1] << endl;
    cout << v[2] << endl;

    // This will fail, best match for this function call is the templated function_1 !
    // function_1(221u);

    function_2(string{"Heineken"});
    function_2(string{"Heineken_bear"});    
    cout << v[3] << endl;
    cout << v[4] << endl;
    
    //This will NOT FAIL
    function_2(221);    
    function_2(221u);    
    cout << v[5] << endl;
    cout << v[6] << endl;

  return 0;
}