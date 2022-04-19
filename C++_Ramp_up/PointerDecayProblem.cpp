#include <iostream>
using namespace std;

// Pointer decay problem 
// When an array is passed to a function, the size and type informations 
// are lost, so inside the function
// The "arr" array decays into a pointer by losing its type and dimension 
// This happens when you pass and array by value, what you are really doing
// is copying a pointer

// At the assembly level all these 3 functions are defined :
// void f(int* arg)

void f(int* arg)
{
    cout << sizeof(arg) << endl;
}

void f2(int arg[])
{
    cout << sizeof(arg) << endl;
}


void f3(int arg[5])
{
    cout << sizeof(arg) << endl;
}


//Passing an array of 5 ints by reference
//You can pass any other type of size for array
void solution(int (&arg)[5])
{
    //Type and dimension informations are retained
    cout << sizeof(arg) << endl;
}

int main()
{

    int arr[5] {1,2,3,4,5};
    int arr2[6] {1,2,3,4,5,6};
    //sizeof(arr) equals 20 (5 * 4B)
    f(arr);
    f2(arr);
    f3(arr);

    solution(arr);

    // ERROR you can't pass an array with size != than 5
    //solution(arr2);

}