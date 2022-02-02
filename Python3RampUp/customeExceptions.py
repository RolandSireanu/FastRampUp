# All your custome defined exceptions have to be derived from a base exception class like Exception or ValueErro etc


class NameTooLong(ValueError):
    pass


def f(name):
    if(len(name) > 10):
        raise NameTooLong(name)
    else:
        raise FileNotFoundError()
        print(name)

try:
    f("Plump")
#This will catch specific "NameTooLong" exceptions
except NameTooLong as err:
    print("Please enter a shorter name")
#This will catch all exceptions derived from "Exception" base class
except Exception as err:
    print("Other exception has been thrown")
else:
#This line is executed if no exceptions have been thrown
    print("Name length is valid ")
finally:
#Finally clause is executed anyway, it is more of a clean-up step
    print("Bye bye !")


# ================ Assert ==================
import sys
try:
    #If expresion is evaluated to FALSE and AssertionError is thrown
    assert(len(sys.argv[1]) > 5)
except AssertionError as err:
    print("Assertion error !")
    print(err)

# ============== Antipaterns using exceptions ==========
# Never do this : 
# It will silently hide all exceptions in you try except block
try:
    #Just a code that throw exceptions
    assert(1 == 2)
except :
    pass

    # One solution is to catch specific exceptions , like ValueError , FileNotFoundEror etc
    # Second solution is to write the entire stack trace in a logging file 
print(" ============================= ")
import traceback
try:
    assert(1 == 2)
except Exception as ex :
    tb_lines = traceback.format_exception(ex.__class__, ex, ex.__traceback__)
    tb_text = "".join(tb_lines)
    print(tb_text)

