// Difference between letting the compiler deducing the type and specifing the type
// Same function template called differently results in completely different code


#include <iostream>
using namespace std;

template<typename T>
void f(T arg)
{
  int j {9};
  T var = j;
}


int main()
{
  	int i {0};
	const int& r = i;
  	
  	
  
  	f<const int&>(i);
  	/*
  	template<>
    void f<const int &>(const int & arg)
    {
      int j = {9};
      const int & var = j;
    }
    */
  
  	f(r);
  	/*
  	template<>
    void f<int>(int arg)
    {
      int j = {9};
      int var = j;
    }
    */
  
    return 0;
}