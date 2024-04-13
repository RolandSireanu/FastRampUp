# How to choose what symbols are exported from a shared library (.so file)?
1. Set the -fvisibility linker flag on hidden, to make all symbols private (-fvisibility=hidden)
2. Add __attribute__((visibility("default"))) to each symbol you want to export (make it public)


In the current example:
1.Compile the shared library with :
	g++ -shared -fpic foo.cpp -fvisibility=hidden  -o libfoo.so

libfoo.so:
00000000000010f9 T add(int, int)	// T = means .text section public symbol
0000000000001111 t mul(int, int)	// t = means .text section private symbol


By adding visibility("default") to `add(int, int)` function, we exported it outside of so file.

