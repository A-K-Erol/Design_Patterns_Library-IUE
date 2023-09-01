import abc
# ============================================================================
# Name        : FactoryMethod.py
#
# The classes and/or objects participating in this pattern are:
# 1. Product  (Engine,Transmission - Abstract)
# Defines the interface of objects the factory method creates
# 2. ConcreteProduct  (OPEL_Engine, OPEL_Transmission)
# Implements the Product interface
# 3. Creator  (CarCreator)
# Declares the factory method, which returns an object of type Product.
# Creator may also define a default implementation of the factory method
# that returns a default ConcreteProduct object.
# May call the factory method to create a Product object.
# 4. ConcreteCreator (OPELCreator)
# Overrides the factory method to return an instance of a ConcreteProduct.
# ============================================================================


# Top "Abstract Product" Part class
class Part:
    @abc.abstractmethod
    def display_name(self):
        pass

    @abc.abstractmethod
    def get_price(self):
        pass


# Engine Base Class
class Engine(Part):
    def __init__(self):
        self._price = None
        self._name = None

    def get_price(self):
        return self._price

    def display_name(self):
        return self._name


# Transmission base class
class Transmission(Part):
    def __init__(self):
        self._price = None
        self._name = None

    def get_price(self):
        return self._price

    def display_name(self):
        return self._name


# A "ConcreteProduct" class
class OPELEngine(Engine):
    def __init__(self, price):
        super().__init__()
        self._price = price
        self._name = "OPEL Engine"
        print("OPEL Engine is created...")


# A "ConcreteProduct" class
class OPELTransmission(Transmission):
    def __init__(self, price):
        super().__init__()
        self._price = price
        self._name = "OPEL Transmission"
        print("OPEL Transmission is created...")


# An 'Abstract Creator' class
class CarCreator:
    # Object creation is delegated to factory.
    def __init__(self):
        self.__parts = []

    def create_engine(self):
        pass

    def create_transmission(self):
        pass

    def create_car(self):
        self.__parts.append(self.create_engine())
        self.__parts.append(self.create_transmission())

    def display_parts(self):
        print("\tListing Parts\n\t--------------\n")
        for p in self.__parts:
            print("\t" + p.display_name() + " " + str(p.get_price()))


# A 'ConcreteCreator' class
class OPELCreator(CarCreator):
    # Factory Method implementation.
    # We are overriding the factory method

    def __init__(self):
        super().__init__()

    def create_engine(self):
        return OPELEngine(25000.00)

    def create_transmission(self):
        return OPELTransmission(10000.00)


# Factory Method Design Pattern.
# Entry point into main application
# Create new OPEL Car
def factory_method():
    creator = OPELCreator()
    print("Creating OPEL")
    creator.create_car()
    creator.display_parts()


if __name__ == "__main__":
    factory_method()
