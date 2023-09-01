import threading
import random

# The classes / objects participating in this pattern are:
# 1. Singleton (Load Balancer)
#       defines and instance operation that lets clients access
#       its unique instance. Instance is a class operation.
#       Responsible for creating and maintaining its own unique instance


class LoadBalancer:
    # class attributes
    lock = threading.Lock()

    def __init__(self, mode):
        self.__servers = ["ServerI", "ServerII", "ServerIII", "ServerIV", "ServerV"]
        self.__mode = mode

    def get_server(self):
        random.seed(random.seed())
        return self.__servers[random.randint(0, 4)]

    def __new__(cls, mode):
        # Thread-safe load-balancer
        # mode 'D' is 'Double-Checked Locking'

        thr_name = threading.current_thread().name + ": "
        if mode == 'D':
            if not hasattr(cls, 'instance'):
                LoadBalancer.lock.acquire()
                print(thr_name + " acquired lock")
                try:
                    if not hasattr(cls, 'instance'):
                        cls.instance = super(LoadBalancer, cls).__new__(cls)
                finally:
                    LoadBalancer.lock.release()
                    print(thr_name + " released lock")
            return cls.instance

        # mode 'N' is 'No Double-Checked Locking'
        elif mode == 'N':
            LoadBalancer.lock.acquire()
            # Lock is acquired and released even if instance already exists
            print(thr_name + " acquired lock")
            try:
                if not hasattr(cls, 'instance'):
                    cls.instance = super(LoadBalancer, cls).__new__(cls)
            finally:
                LoadBalancer.lock.release()
                print(thr_name + " released lock")
            return cls.instance

        else:
            print("Please specify mode: 'D' for Double-Checked or 'N' for Single-Checked Locking")


def my_runnable(mode):
    thr_name = threading.current_thread().name + ":"
    lb = LoadBalancer(mode)
    print(thr_name + " load balancer <" + lb.__repr__() + ">")


def singleton_pattern_multithread():
    # Test 1
    print("START DOUBLE CHECKED LOCKING")
    t1 = threading.Thread(target=my_runnable, name="t1", args='D')
    t2 = threading.Thread(target=my_runnable, name="t2", args='D')
    t3 = threading.Thread(target=my_runnable, name="t3", args='D')
    # We have to create a scenario in which threads are starting
    # sequentially to show the tradeoffs of double-checking
    t1.start()
    t1.join()
    t2.start()
    t2.join()
    t3.start()
    t3.join()

    # Test 2
    print("\nSTART NO-DOUBLE CHECKED LOCKING")
    t1 = threading.Thread(target=my_runnable, name="t1", args='N')
    t2 = threading.Thread(target=my_runnable, name="t2", args='N')
    t3 = threading.Thread(target=my_runnable, name="t3", args='N')
    # We have to create a scenario in which threads are starting
    # sequentially to show the real advantage of double-checking
    t1.start()
    t1.join()
    t2.start()
    t2.join()
    t3.start()
    t3.join()


if __name__ == "__main__":
    singleton_pattern_multithread()
