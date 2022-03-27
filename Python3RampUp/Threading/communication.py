from ast import arg
from queue import Queue
import threading

def producer(data, q : Queue):
    for item in data:
        evt = threading.Event()
        q.put((item, evt))

        evt.wait()

def consumer(q:Queue):
    while True:
        data, ev = q.get()
        print(data * 2)
        ev.set();
        q.task_done()


def main():
    q = Queue()
    data = [10,50,10,40,30];
    threading.Thread(target=producer, args=(data,q)).start()
    threading.Thread(target=consumer, args=(q,)).start()

    q.join()

if __name__ == "__main__":
    main();