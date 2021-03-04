
def gen():
    for i in range(100):
        yield i;


def gen2():
    for i in range(100,200):
        yield i;

def bigGen():
    yield from gen();
    yield from gen2();

if __name__ == "__main__":
    for i in bigGen():
        print(i)
    # for e in gen():
    #     print(e)