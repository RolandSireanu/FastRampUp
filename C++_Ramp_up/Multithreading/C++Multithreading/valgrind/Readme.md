This tells Valgrind to print out a suppression for each reported error, which you can then copy into a suppressions file.
    --gen-suppressions=yes
That makes it easier to see the function-call
    -fno-inline. 
Produce code with no optimization or max -O1
Compile the code with -Wall
Redirect the output to file or socket
    --log-file=filename
    --log-socket=192.168.0.1:12345
Tool selection:
    --tool=<toolname>  e.g. memcheck, cachegrind, callgrind, helgrind, drd, massif, dhat, lackey, none, exp-bbv
        memcheck:           Illegal memory access, use of uninitialized memory, and incorrect memory freeing operations, memory leaks
        cachegrind:         It provides detailed cache usage information, which helps identify bottlenecks and improve program performance by optimizing cache usage.
        callgrind:          Generates call graphs showing how many calls were made to each function and the cost (in terms of time) incurred by each function.
        helgrind, drd:      Helgrind is a Valgrind tool for detecting synchronisation errors in C, C++ and Fortran programs that use the POSIX pthreads threading primitives.
        massif,dhat:        Massif is a heap profiler that measures the heap memory usage of your program.
        lackey:             Count number of instructions executed for improving the performance
        none:               It is often used to measure the overhead introduced by Valgrind itself, since running "None" provides a baseline for how much slower a program 
                            might run under the influence of the Valgrind infrastructure without any additional analysis. Developers may use "None" to verify that Valgrind's 
                            basic program execution and simulation mechanisms are functioning correctly
        exp-bbv:            Experimental tool designed for detecting bugs related to uninitialized memory