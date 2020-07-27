

def upperDecorator(f):
    def wrapper(*args , **kwargs):
        temp = f(*args,**kwargs)
        return temp.upper();
    return wrapper;

@upperDecorator
def printSms(message):
    return message;

print(printSms("Roland merge la mare !"))
