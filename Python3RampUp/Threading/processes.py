from multiprocessing import Process, Queue

def producer(arg_data, q:Queue):
    """
    Producer from producer-consumer pattern
    """
    for data in arg_data:
        q.put(data)
    q.put(-1)

def consumer(q:Queue):
    while True:
        currentData = q.get()
        print(f"Consumer is processing {currentData}")
        if currentData == -1:
            break;

def main():
    database = ["Elefant", "Zimbru", "Cocos", "Caine", "Elan"]
    q = Queue()
    p1 = Process(target=producer, args=(database,q))
    p2 = Process(target=consumer, args=(q,))
    p1.start();
    p2.start();

    q.close()
    q.join_thread()

    p1.join()
    p2.join()



if __name__ == "__main__":
    main()