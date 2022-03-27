from concurrent.futures import thread
import threading
import logging

total = 0
#Reentrat mutex, same thread can acquire the lock multiple times
#after it has already acquired.
lock = threading.RLock()

def get_logger():
    logger = logging.getLogger("Threading example")
    logger.setLevel(logging.DEBUG)

    fh = logging.FileHandler("threading.log")
    fmt = "%(asctime)s - %(threadName)s - %(levelname)s - %(message)s"
    formatter = logging.Formatter(fmt)
    fh.setFormatter(formatter);

    logger.addHandler(fh)
    return logger;

logger = get_logger()

def increment():
    global total
    lock.acquire()
    logger.debug("Lock acquired ")
    try:
        total = total + 1;  
        logger.debug(f"total = {total}");
    finally:
        lock.release()
        logger.debug("Lock released")

def decrement():
    global total
    lock.acquire()
    try:
        total = total + 1;
        logger.debug(f"total = {total}");
    finally:
        lock.release()

def main():
    with lock:
        increment()
        decrement()


if __name__ == "__main__":
    for i in range(64):
        threading.Thread(target=main).start()
    