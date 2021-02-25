#include <iostream>
#include <variant>
#include <string>
using namespace std;

//std::variant
//One variable can take multiple value types


enum class ErrorCode : int
{
    NO_ERROR=0, FILE_NOT_FOUND=1, BUSY=2
};

variant<string, ErrorCode> readFromFile(int arg)
{
    if(arg % 2 == 0)
    {
        return "Nr par ";
    }
    else
    {
        return ErrorCode::FILE_NOT_FOUND;
    }
} 

int main()
{
    auto value = readFromFile(3);
    //Index of the return type , 0 string , 1 ErrorCode
    cout << value.index() << endl;
    if(value.index() == 0)
    {
        cout << std::get<0>(value) << endl;
    }
    else
    {
        //std::get<1>(value) , and threat the error
        cout << " Error ! " << endl;
    }

    // A better way to access the return value is with get_if

    auto ptr = get_if<string>(&value);
    if(ptr != nullptr)
    {
        cout << *ptr << endl;
    }
    else
    {
        cout << "Error with code " << static_cast<int>(get<1>(value)) << endl;
    }

    return 0;
}