using namespace std;

int main()
{
    //adornments
    //from all the adornments (ref, const, ptr( auto type specifier is keeping just the pointer type
    //the rest are denied

    int var = 5;
    int& ref_var = var;
    const int& const_ref_var = var;
    int* ptr_var = &var;

    auto temp1 = var;           // int
    auto temp2 = ref_var;       // int 
    auto temp3 = const_ref_var; // int
    auto temp4 = ptr_var;       // int *    the only case when auto keeps something from initializer type

    const auto& temp5 = var;    // const int&
    const auto* temp6 = var;    // const int*

    return 0;
}