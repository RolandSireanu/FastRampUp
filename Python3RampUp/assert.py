
#assert can't be used for data validaton because it can easily be disabled at cpython compile time
#used mainly for debug 


def discount(price,percentage):
    finalPrice = price - price * percentage;
    assert 0 <= finalPrice < price , "Wrong computed value for final price";
    return finalPrice;


print(discount(150,1.25))


#This cond will be always true , the correct form is assert 1==2,"Error"   ,without '()' 
assert(1==2,"Error")
