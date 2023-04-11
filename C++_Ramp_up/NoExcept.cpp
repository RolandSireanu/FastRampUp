#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <span>
using namespace std;

/* What NOEXCEPT does actually mean?
    It has two different meanings:
        - This function will never throw an exception. It doesn't use new, 
           call a library function that might use new, 
           perform any arithmetic that might overflow or underflow, 
           or in any other way cause any kind of exception to be thrown.
        - This function will never throw an exception that can be caught and recovered from. 
          If anything it does causes any kind of exception to be thrown, it is pointless to unwind the stack 
          and go through the catch process, 
          because things are in such a terrible state that recovering will not be possible. Just terminate.

    if you're able to mark a function noexcept, you'll make your application faster in two entirely different ways: 
        - First, the compiler doesn't have to do a certain amount of setup -- essentially the infrastructure 
          that enables stack unwinding, and teardown on the way into and out of your function -- 
          if no exceptions will be propagating up from it. 
        - Standard Library is noexcept-aware and uses it to decide between copies and moves.
          You really want your moves to be noexcept. And if your moves use some other member functions of your class, you want those to be noexcept
*/


int main()
{
}
