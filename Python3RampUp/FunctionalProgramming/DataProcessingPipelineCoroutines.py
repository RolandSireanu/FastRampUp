def filter1(arg, nextGen):
    while True: 
        print(arg)
        value = yield
        print("Value = " + str(value))
        nextGen.send(value/2)

def filter2(nextGen):
    while True:
        value = yield 
        print("Value = " + str(value))
        nextGen.send(value/2)

def filter3():
    while True:
        value = yield 
        print("Value = " + str(value))

f3 = filter3()
f2 = filter2(f3)
f1 = filter1("divider", f2)

next(f1);   next(f2);   next(f3);

f1.send(128)
print(" ==== ")
f1.send(512)

# Output : 
# divider
# Value = 128
# Value = 64.0
# Value = 32.0
# divider
#  ==== 
# Value = 512
# Value = 256.0
# Value = 128.0
# divider
