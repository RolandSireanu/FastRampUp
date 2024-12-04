#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

// Two types are related to each other if there is a conversion between them.
// Implicit conversions occur :
//      -> in most expr values < int are promoted to an appropriate larget int type
//      -> non bool are converted to bool
//      -> the right hand operand is conv to type of left-hand operand in initializations        
//      -> In arithmetic expr, both operand are conv to a common one. (widest type)

// In principiu cand au aceelasi semn , expr aritmetica se converteste la tipu
// cel mai mare. Intre intreg si float se conv al float
// Cand au semne diferite :
// Tipul operatorului unsigned >= tipul op cu semn => op cu semn se conv la unsigned
//   unsigned int and int => int -> unsigned int


int main()
{
    // implicit conversion
    // step 1 : 2 is converted to double
    // step 2 : fp addition is done, result is a double
    // step 3 : initialization, type of object we are initializing
    //          dominates. Converting double to int and initialize ival
    // int ival = 3.15 + 2;

    bool flag;      char cval;
    short sval;     unsigned short usval;
    int ival;       unsigned int uival;
    long lval;      unsigned long ulval;
    float fval;     double dval;

    3.1400000000000000001L + static_cast<long double>(static_cast<int>('b'));
    dval + static_cast<double>(ival);
    static_cast<double>(fval) + dval;
    fval + static_cast<float>(ival);
    ival = static_cast<int>(dval);
    static_cast<int>(sval) + static_cast<int>(cval);
    static_cast<float>(static_cast<int>(cval)) + fval;
    static_cast<long>(cval) + lval;
    static_cast<unsigned long>(ival) + ulval;

    // Implicit conversion to bool
    char* text = "Implicit conversions";
    // Expr is true of text is != nullptr 0
    if (text){

    }


    // ======== Implicit conversions to const ========
    // We can convert a pointer to non const tyoe to a pointer
    // to the coresponding const type and similarly for references.
    const int& rival = ival;
    const int* cpival = &ival;
    int * pival = &ival;
    const int* cpival2 = pival;


    // ======= Implicit conversions defined by class type ======
    // cin will be converted to bool using the defined 
    // conversion from isteam to bool , and evaluated
    // while (cin >> s ) {}

    return 0;
}