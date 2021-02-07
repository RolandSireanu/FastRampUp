#include <iostream>

// Shared_ptr
//Downsides : 
    // Twice as big as raw pointer , internally contain raw pointer to resource and raw pointer to 
    // control block (reference counter)

    //Memory for the control block has to be dynamically allocated. 
    //When make_shared can be used , this cost of allocation is eliminated because make_shared 
    //make 1 allocation for data and control block

    //Reference count is atomic , and atomic operations are always slower 

//Even with custom deleter  and allocator , a shared_ptr is constant in size , because
//pointer to deleter and allocator are stored in control block together with reference count and weak count

//Using custom deleter is not possible with make_shared
//Don't pass raw pointers to shared_ptr , if there are other shared_ptr pointing to the same raw pointer
//this will result in undefined behaviour

int main()
{



    return 0;
}