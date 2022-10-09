#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

struct my_type{};

template<typename T, typename=void>
struct is_comparable 
{
    static constexpr bool value = false; 
};

template<typename T>
struct is_comparable<T, decltype((declval<T>() != declval<T>()), void())>
{
    static constexpr bool value = true; 
};


int main()
{
  	// ===== Step 1, based of generalization, a specialization is generated:
    // template<>
    // struct is_comparable<int, void>
    // {
    //  inline static constexpr const bool value = true;
    // };
    if(is_comparable<int>::value)
        cout << "Yes it is " << endl;
    else
        cout << "No it isn't " << endl;
	
  	// ====== Step 2, if a user defined specialization exists, use it instead of 
    // generating a new one. So, if our specialization generates <T,void>, it  will alwasy be 
    // choosen against the generaliazation, if not, generaliaztion will be used.

    return 0;
}
