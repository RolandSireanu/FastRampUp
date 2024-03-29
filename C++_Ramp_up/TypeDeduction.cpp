
// During compilation, compilers use expr to deduce two types: one for T and one for
// ParamType. These types are frequently different, because ParamType often contains
// adornments, e.g., const or reference qualifiers.

//For printing the deduced type at runtime , the best option is : <boost/type_index.hpp>
// type_info is not reliable


// ========================== Info generala ============================
//  T este tipul argumentului fara referinta daca exista
//  ParamType este T concatenat cu & sau cu && 
// =====================================================================


//Case 1 : ParamType is a reference or a pointer type
//      -> daca tipul expresiei este referinta, in T se ignora referinta
//      -> se concateneaza T cu & 



template<typename T>
void c1(T& arg)
{}

template<typename T>
void c11(const T& arg)
{}

template<typename T>
void c111(T* arg)
{}


//Case 2 : ParamType is a universal reference
//      Daca tipul expresiei este lvalue , ParamType este egal cu T (T concatenat cu &)
//      Daca tipul expresiei este rvalue , 
template<typename T>
void c2(T&& arg)
{}

//Case 3 : ParamType is neither a pointer nor a reference
//         const, volatile sau referinta sunt ignorate, T este egal cu ParamType egal cu tipul expr fara (const,ref,volatile)
template<typename T>
void c3(T arg)
{}


int main()
{
    int a = 1;
    const int b = 23;
    int& r = a;
    int&& rref = 3;
    const int &cr = a;

    //=================================================================
    c1(a);      //T = int ,         ParamType = int&
    c1(b);      //T = const int ,   ParamType = const int&
    c1(r);      //T = int,          ParamType = int&
    c1(cr);     //T = const int ,   ParamType = const int&
  	c1(rref);	//T = int		,   ParamType = int&

    c11(a);     //T = int ,         ParamType = const int&
    c11(b);     //T = int ,         ParamType = const int&
    c11(cr);    //T = int ,         ParamType = const int&
   	c11(rref);  //T = int , 		ParamType = const int&

    c111(&a);   //T = int ,         ParamType = int*
    c111(&b);    //T = const int ,  ParamType = const int*    


    //c1(T& arg)
    //void c11(const T& arg)
    //void c2(T&& arg)
    //void c3(T arg)

    //=================================================================

    c2(a);      //T = int&,         ParamType = int&
    c2(b);      //T = const int&,   ParamType = const int&
    c2(r);      //T = int&          ParamType = int&
    c2(9);      //T = int,          ParamType = int&&
  	c2(rref);	//T = int,			ParamType = int&&

    //=================================================================
    c3(a);      //T = int , ParamType = int
    c3(b);      //T = int , ParamType = int
    c3(r);      //T = int , ParamType = int
    c3(cr);     //T = int , ParamType = int
	c3(rref);	//T = int , ParamType = int


    return 0;
}