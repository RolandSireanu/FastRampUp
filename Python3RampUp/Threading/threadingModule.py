import logging
import threading

def get_logger():
    logger = logging.getLogger("Threading example")
    logger.setLevel(logging.DEBUG)

    fh = logging.FileHandler("threading.log")
    fmt = "%(asctime)s - %(threadName)s - %(levelname)s - %(message)s"
    formatter = logging.Formatter(fmt)
    fh.setFormatter(formatter);

    logger.addHandler(fh)
    return logger;

class MyThread(threading.Thread):

    def __init__(self, number, logger):
        # threading.Thread.__init__(self)
        super().__init__();
        self.number = number
        self.logger = logger

    def run(self):
        """
        Run the thread
        """
        logger.debug('Calling doubler')
        doubler(self.number, self.logger)

def doubler(arg_nr, arg_logger):
    """
        Just doubles a value
    """

    arg_logger.debug("doubler function executing")
    result = arg_nr * 2;
    arg_logger.debug(f"doubler function ended with {result}")

if __name__ == "__main__":
    logger = get_logger()
    thread_names = ["Roland","Alexandru","Dragos","Ioana"]
    for i in range(len(thread_names)):
        my_thread = MyThread(i, logger);
        my_thread.setName(thread_names[i])
        my_thread.start();
        # my_thread = threading.Thread(
        #     target=doubler, 
        #     name = thread_names[i],
        #     args=(i*2,logger)
        # )
        # my_thread.start()
