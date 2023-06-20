#include <iostream>

int main()
{
    int v {5};


    // Use switch case instead of multiple ifs
    switch (v)
    {
        case 1:
            //Switch case is build based on jumps
            //The compiler jumps the execution at the right case and unless it hits a break
            //statement it will continue to execute from there.
            break;

        case 2:
            break;
    }   
    return 0;
}