To understand circular dependencies, you need to remember that Python is essentially a scripting language. Execution of statements outside methods occurs at compile time. Import statements are executed just like method calls, and to understand them you should think about them like method calls.

When you do an import, what happens depends on whether the file you are importing already exists in the module table. If it does, Python uses whatever is currently in the symbol table. If not, Python begins reading the module file, compiling/executing/importing whatever it finds there. Symbols referenced at compile time are found or not, depending on whether they have been seen, or are yet to be seen by the compiler.

Imagine you have two source files:

File X.py

def X1:
    return "x1"

from Y import Y2

def X2:
    return "x2"
File Y.py

def Y1:
    return "y1"

from X import X1

def Y2:
    return "y2"
Now suppose you compile file X.py. The compiler begins by defining the method X1, and then hits the import statement in X.py. This causes the compiler to pause compilation of X.py and begin compiling Y.py. Shortly thereafter the compiler hits the import statement in Y.py. Since X.py is already in the module table, Python uses the existing incomplete X.py symbol table to satisfy any references requested. Any symbols appearing before the import statement in X.py are now in the symbol table, but any symbols after are not. Since X1 now appears before the import statement, it is successfully imported. Python then resumes compiling Y.py. In doing so it defines Y2 and finishes compiling Y.py. It then resumes compilation of X.py, and finds Y2 in the Y.py symbol table. Compilation eventually completes w/o error.

Something very different happens if you attempt to compile Y.py from the command line. While compiling Y.py, the compiler hits the import statement before it defines Y2. Then it starts compiling X.py. Soon it hits the import statement in X.py that requires Y2. But Y2 is undefined, so the compile fails.

Please note that if you modify X.py to import Y1, the compile will always succeed, no matter which file you compile. However if you modify file Y.py to import symbol X2, neither file will compile.

Any time when module X, or any module imported by X might import the current module, do NOT use:

from X import Y
Any time you think there may be a circular import you should also avoid compile time references to variables in other modules. Consider the innocent looking code:

import X
z = X.Y
Suppose module X imports this module before this module imports X. Further suppose Y is defined in X after the import statement. Then Y will not be defined when this module is imported, and you will get a compile error. If this module imports Y first, you can get away with it. But when one of your co-workers innocently changes the order of definitions in a third module, the code will break.

In some cases you can resolve circular dependencies by moving an import statement down below symbol definitions needed by other modules. In the examples above, definitions before the import statement never fail. Definitions after the import statement sometimes fail, depending on the order of compilation. You can even put import statements at the end of a file, so long as none of the imported symbols are needed at compile time.

Note that moving import statements down in a module obscures what you are doing. Compensate for this with a comment at the top of your module something like the following:

#import X   (actual import moved down to avoid circular dependency)
In general this is a bad practice, but sometimes it is difficult to avoid.