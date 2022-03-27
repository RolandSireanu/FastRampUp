import requests
import time
import threading
import sys

def req():
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')

def withoutThreading():
    now = time.time()
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    r = requests.get('https://api.spotify.com/v1/search?type=artist&q=snoop')
    print(f"No threads runtime : {time.time() - now}s")
# print(time.time() - now)

def showA():
    for i in range(50):
        result = ((i * i)/0.15)
        print(f"showA {result}")

def showB():
    for i in range(50):
        result = ((i * i)/0.15)
        print(f"showB {result}")

def main():
    l = [threading.Thread(target=req) for i in range(10)]
    
    now = time.time()
    for th in l:
        th.start();
    for th in l:
        th.join()
    print(f"With threading runtime : {time.time() - now}")

    withoutThreading()
    # How often does a thread is switched
    sys.setswitchinterval(1)




if __name__ == "__main__":
    main();
