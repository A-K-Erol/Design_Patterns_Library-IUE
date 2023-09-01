from threading import Lock
from random import seed
from random import randint
# The classes / objects participating in this pattern are
# 1. Singleton (Load Balancer)
#       Defines an Instance operation that lets clients access its unique
#       Instance. Instance is a class operation. Responsible for creating
#       and maintaining its own instance


# This is the 'Singleton' class
class LoadBalancer:
    # static class variables
    lock = Lock()

    # returns instance if it exists, else makes new one
    # uses 'Double-Checked Locking' for multithread safety
    def __new__(cls):
        if not hasattr(cls, 'instance'):
            LoadBalancer.lock.acquire()
            print("Acquired Lock")
            try:
                if not hasattr(cls, 'instance'):
                    cls.instance = super(LoadBalancer, cls).__new__(cls)
            finally:
                LoadBalancer.lock.release()
                print("Released Lock")
        return cls.instance
    
    # initializes a list of 5 servers
    def __init__(self):
        self.__servers = ["ServerI", "ServerII", "ServerIII", "ServerIV", "ServerV"]

    # simple load balancer
    def get_server(self):
        seed(seed())
        return self.__servers[randint(0, 4)]


def singleton():
    # instantiate LoadBalancers
    lb1 = LoadBalancer()
    lb2 = LoadBalancer()
    lb3 = LoadBalancer()

    # same instance?
    if lb1 == lb2 and lb2 == lb3:
        print("Same Instance")

    print("load balancer 1: " + lb1.__repr__())
    print("load balancer 2: " + lb2.__repr__())
    print("load balancer 3: " + lb3.__repr__())

    # All are the same instance, use lb1 arbitrarily
    # Load Balance 15 server requests

    print("Generating requests... ")
    for i in range(15):
        print(lb1.get_server())


if __name__ == "__main__":
    singleton()
