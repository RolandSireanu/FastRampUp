import functools

def worker(a, b, op):
    if op == "sum":
        return a + b;
    elif op == "diff":
        return a - b;
    else:
        return a * b;
    
        
addition = functools.partial(worker, op="sum")
print(addition(10,11))
