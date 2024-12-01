#include <iostream>
#include <string>

namespace Auto
{
class Car
{    
public:
    Car(std::string const& aBrand, int const& aHp) : mBrand{aBrand}, mHp{aHp} 
    {}

    Car() = default;
    friend void swap(Car&, Car&);

    void printMe()
    {
        std::cout << "Brand = " << mBrand << " , Hp = " << mHp << std::endl;
    }
private:
    std::string mBrand;
    int mHp;
};

void swap(Car& aCar1, Car& aCar2)
{
    std::cout << "Swap from Auto namespace used " << std::endl;
    Car temp;
    temp.mBrand = std::move(aCar2.mBrand);
    aCar2.mBrand = std::move(aCar1.mBrand);
    aCar1.mBrand = std::move(temp.mBrand);
}
};

class ShowRoom
{
public:
    Auto::Car mCar;
    std::string mName;
};

// This version of swap uses the standard implementation of swap function although for mCar there is
// a specific implementation in Auto namespace. 
// void swap(ShowRoom& aArg1, ShowRoom& aArg2)
// {        
//     std::swap(aArg1.mCar, aArg2.mCar);      // Qualified name lookup
//     std::swap(aArg1.mName, aArg2.mName);    // Qualified name lookup
// }


// This is a more flexible implementation of swap function for ShowRoom type because it takes into consideration
// the specific implementations of swap function for each type having also a fallback implementation std::swap
void swap(ShowRoom& aArg1, ShowRoom& aArg2)
{
    using std::swap;                        // Fallback for types without specific implementation of swap function
    // This is called a CUSTOMIZATION POINT
    swap(aArg1.mCar, aArg2.mCar);           // Unqualified lookup, compiler will find the template std::swap
                                            // and through ADL our swap function from Auto namespace.
                                            // The Auto::swap function is choosen over the template std::swap
    swap(aArg1.mName, aArg2.mName);
}


int main()
{

    ShowRoom lShow1;
    ShowRoom lShow2;

    swap(lShow1, lShow2);

    return 0;
}