#include <iostream>
#include <optional>
#include <string>
using namespace std;

//What to return when you covered just the positive case ?
//For example , return string from a file , but the file is empty 
//You will have to return a predefined value to mark the empty
//file event. 
//This is not the case with std::optional

optional<string> readFile(int nr)
{
    if(nr%2 == 0)
        return "nr par ";
    else
        return optional<string>();
}



int main()
{

    optional<string> val = readFile(3);

    //If empty optional is returned , default value is set
    val.value_or("Empty file ");

    if(val.has_value())
    {
        std::cout <<"Ret value " << val.value() << std::endl;
    }
    else
    {
        cout << "No value returned ! " << endl;
    }

    return 0;
}