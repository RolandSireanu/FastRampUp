#include <dlfcn.h>
#include <iostream>

void testFunction();


int main()
{
    void* libhandle = dlopen("/Users/sireanuroland/Work/SystemProgrammingLinux/SharedObjects/build/libmylib.dylib", RTLD_LAZY);

    if (libhandle == NULL) {
        std::cout << "unable to load Library!" << std::endl;
        return 1;
    }

    int (*opfunc)(int);
    opfunc = dlsym(libhandle, "do_operation");

    return 0;
}