import abc
# Name: ObserverPattern.py

# The classes / objects participating in this pattern are:
# The classes and/or objects participating in this pattern are:
# 1. Subject  (Stock)
#    	. Knows its observers. Any number of Observer objects may observe a subject.
#       . Provides an interface for attaching and detaching Observer objects.
# 2. ConcreteSubject  (IBM)
#       . Stores state of interest to ConcreteObserver sends a notification to its.
#   	. Observers when its state changes.
# 3. Observer  (Investor)
#       . Defines an updating interface for objects that should be notified
#       of changes in a subject.
# 4. ConcreteObserver  (Investor)
#       . Maintains a reference to a ConcreteSubject object
#       . Stores state that should stay consistent with the subject's
#       . Implements the Observer updating interface to keep its state
#         consistent with the subject's


# Subject ==> Stock
class Stock:
    def __init__(self, symbol, price):
        self._symbol = symbol
        self._price = price
        self._investors = []

    # Register the observers
    def attach(self, investor):
        self._investors.append(investor)

    # De-register observer
    def detach(self, investor):
        self._investors.remove(investor)

    # Notify observers
    def notify(self):
        # Set argument to something that helps
        # tell observers what happened
        for investor in self._investors:
            investor.update(self)

    def get_symbol(self):
        return self._symbol

    def set_symbol(self, value):
        self._symbol = value

    def get_price(self):
        return self._price

    def set_price(self, price):
        self._price = price


# ConcreteSubject ==> IBM
class IBM(Stock):
    # Constructor
    def __init__(self, symbol, price):
        super().__init__(symbol, price)
        self.__name = "IBM"

    def get_price(self):
        return self._price

    def set_price(self, value):
        self._price = value
        self.notify()

    def get_name(self):
        return self.__name


# Observer ==> Abstract Observer
class Observer:
    @abc.abstractmethod
    def update(self, stock):
        pass


# Concrete Observer
class Investor(Observer):
    def __init__(self, name):
        self.__stock = None
        self.__investor_name = name
        self.__stock_price = None  # internal observer state
        self.__stock_name = None  # internal observer state

    def update(self, stock):
        self.__stock = stock  # reference to subject
        self.__stock_price = stock.get_price()
        self.__stock_name = stock.get_name()
        print("Notified " + self.__investor_name + " of " + self.__stock_name
              + "'s change to " + str(self.__stock_price))

    def get_stock(self):
        return self.__stock

    def set_stock(self, value):
        self.__stock = value

    def get_name(self):
        return self.__investor_name


# test application
def observer_pattern():
    # Create investors
    s = Investor("Alp")
    b = Investor("Aysu")

    # Create new IBM stock and attach investors
    ibm = IBM("IBM", 120.00)
    s.set_stock(ibm)
    b.set_stock(ibm)
    ibm.attach(s)
    ibm.attach(b)

    # Change price and notify investors
    ibm.set_price(120.10)
    ibm.set_price(121.00)
    ibm.set_price(120.50)
    ibm.set_price(120.75)

    print("Removing Aysu from Notification list")
    ibm.detach(b)
    ibm.set_price(121.00)
    ibm.set_price(122.00)
    ibm.set_price(123.00)
    ibm.set_price(124.00)

    ibm = None   # Candidate for Garbage Collection
    # Danger: We have a dangling reference in our observer,
    # remember our implementation issues discussion in lecture.

    print(s.get_stock())  # Reference still has a value


if __name__ == "__main__":
    observer_pattern()
