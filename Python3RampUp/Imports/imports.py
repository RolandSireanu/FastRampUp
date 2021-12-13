# Every module (or python file) has an private symbol table which acts like a 
# global symbol table for objects defined inside module
# When the interpreter executes the above import statement, it searches for mod.py in a list of directories gathered from the following sources:
#   - The directory from where the input script was run or the current directory if the interpreter is being run interactively.
#   - The list of directories contained in the PYTHONPATH environment variable, if it is set. (The format for PYTHONPATH is OS-dependent but should mimic the PATH environment variable.)
#   - An installation-dependent list of directories configured at the time Python is installed.
# After importing "module1" , it is placed in the local symbol table, making it available in the
# caller's context.
# With import intruction you can import just modules , not packages
import module1

print(module1.myFunction());
obj = module1.MyClass();
print(obj.myAttr);


# You can import just a part of the module
# By doing this you place the myList in the local symbol table making it available to the caller,
# any objects that already exist with the same name will be overwritten:

from module1 import myList
print(myList);


# Import a module from a different directory
import pathToModule.module
print(pathToModule.module.add(2,3));


#Import module from a package
import package.moduleInPackage
print(package.moduleInPackage.tellMeSomethingFunny());

