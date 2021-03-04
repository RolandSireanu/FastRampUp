import asyncio
import ipdb
import random 

async def isPrime(arg:int) -> bool :
    return not any(arg % i == 0 for i in range(2,arg-1))

async def primesIn(start:int, end:int, w:int) -> int:
    counter=0;

    for i in range(start,end):
        r = await isPrime(i)
        if(r):
            print("From {} to {} ".format(start,end))
            counter = counter + 1;
            await asyncio.sleep(w);
    print("Returns {}".format(counter))
    return counter;
        

async def generateRandom(threshold:int = 7) -> int :
    nr = random.randint(0,10);

    while(nr < threshold):
        nr = random.randint(0,10);
        await asyncio.sleep(1);
        print("Not found yet : {}".format(nr))

    print("Found it ! {}".format(nr))
    return nr;

async def main():
    #await asyncio.gather(*(generateRandom(i) for i in range(6,9)))
    r = await asyncio.gather(*(primesIn(10,100,1), primesIn(100,1000,0.01),primesIn(100,1100,0.1)));
    print(*r)

if __name__ == "__main__":
    
    asyncio.run(main())

    