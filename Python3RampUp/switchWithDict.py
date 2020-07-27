

def add(x,y):
    return x+y;

def sub(x,y):
    return x-y;

def defaultF(x,y):
    return None;

d = {
        "addition":add, 
        "substraction":sub
};


operand = "addition"

print(d.get(operand , defaultF)(2,3))

print(d.get("multiplication", defaultF)(2,3))
