import aiohttp
import asyncio
import requests
import time

#============================================
#   https://snarky.ca/how-the-heck-does-async-await-work-in-python-3-5/#
#============================================

#Parallel processing through asyncio 
#When await is hit , the coroutine is stoped at that point until the result is available
#and object is send to event loop to be run async
#await = yield from , but onlu on awaitable objects

async def getSlowHtml():

    resp = requests.get("http://www.amazon.com");
    text = resp.text;
    print(f"Downloaded {len(text)}")

async def getHtml(name, queue:asyncio.Queue):
    print(f"Start {name} ... ")
    async with aiohttp.ClientSession() as sess:
        while not queue.empty():
            print(f"Pop tasks from queue {name} ")
            url = await queue.get();
            print(f"Task {name} getting URL: {url}")

            async with sess.get(url) as resp:
                print(f"Now will wait for text on task {name} ...")
                await resp.text()
                print(f"Text received on task {name} !")

async def computation():
    counter=0;
    for i in range(1000000):
        if i%2 == 0:
            counter = counter + 1



async def main():

    work_queue = asyncio.Queue()

    for url in ["http://google.com",
                "http://yahoo.com",
                "http://apple.com",
                "http://microsoft.com",
                "http://olx.ro",
                "http://amazon.com",
                "http://emag.ro"]:

        await work_queue.put(url);

    await asyncio.gather(getHtml("Task1", work_queue),
                   getHtml("Task2", work_queue),
                   getHtml("Task3", work_queue),
                   getHtml("Task4", work_queue),
                   computation(),computation(),computation(),
                   getSlowHtml(), getSlowHtml(), getSlowHtml());

if __name__ == "__main__":
    t1 = time.time()
    asyncio.run(main());    
    t2 = time.time();
    print(t2-t1);