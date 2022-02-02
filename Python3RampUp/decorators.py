
def prefixDecorator(f):

    def wrapper():
        temp=f()
        return "DEBUG:"+temp;

    return wrapper;



def uppercaseDecorator(f):

    def wrapper():
        intermediateResult = f();
        return intermediateResult.upper()

    return wrapper;



# =============================== Stacking decorators ================================== #

# p = uppercaseDecorator(p)
# p = prefixDecorator(p)
@uppercaseDecorator
@prefixDecorator
def p():
    return "Something";


print(p())

# ================================ Decorators with arguments ============================= #
def upperDecorator(f):
    def wrapper(*args , **kwargs):
        temp = f(*args,**kwargs)
        return temp.upper();
    return wrapper;

@upperDecorator
def printSms(message):
    return message;

print(printSms("Roland merge la mare !"))