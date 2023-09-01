import abc
# ============================================================================
# Name        : AbsFactoryMethod.py
#
# The classes and/or objects participating in this pattern are:
# 1. Abstract Product  (Engine,Transmission - Abstract)
# Defines the interface of objects the factory method creates
# 2. ConcreteProduct  (OPEL_Engine, FORD_Transmission)
# Implements the Product interface
# 3. Abstract Creator  (CarCreator)
# Declares the factory method, which returns an object of type Product.
# Creator may also define a default implementation of the factory method
# that returns a default ConcreteProduct object.
# May call the factory method to create a Product object.
# 4. ConcreteCreator (OPELCreator, FORDCreator)
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


# 'Concrete Product' A1
class OPELEngine(Engine):
    def __init__(self, price):
        super().__init__()
        self._price = price
        self._name = "OPEL Engine"
        print("OPEL Engine is created...")


# 'Concrete Product' A2
class FORDEngine(Engine):
    def __init__(self, price):
        super().__init__()
        self._price = price
        self._name = "FORD Engine"
        print("FORD Engine is created...")


# Transmission base class
class Transmission(Part):
    def __init__(self):
        self._price = None
        self._name = None

    def get_price(self):
        return self._price

    def display_name(self):
        return self._name


# 'ConcreteProduct' B1
class OPELTransmission(Transmission):
    def __init__(self, price):
        super().__init__()
        self._price = price
        self._name = "OPEL Transmission"
        print("OPEL Transmission is created...")


# 'ConcreteProduct' B2
class FORDTransmission(Transmission):
    def __init__(self, price):
        super().__init__()
        self._price = price
        self._name = "FORD Transmission"
        print("FORD Transmission is created...")


# An 'AbstractFactory' class
class CarFactory:
    def create_engine(self):
        pass

    def create_transmission(self):
        pass


# A 'ConcreteFactory' class
class OPELFactory(CarFactory):
    def create_engine(self):
        return OPELEngine(25000.00)

    def create_transmission(self):
        return OPELTransmission(10000.00)


# Another 'ConcreteFactory' class
class FORDFactory(CarFactory):
    def create_engine(self):
        return FORDEngine(20000.00)

    def create_transmission(self):
        return FORDTransmission(12000.00)


# The Client
class BuildCar:
    def __init__(self):
        self.__parts = []

    def create_car(self, factory):
        self.__parts.append(factory.create_engine())
        self.__parts.append(factory.create_transmission())

    def display_parts(self):
        print("\tListing Parts\n\t--------------")
        for p in self.__parts:
            print("\t" + p.display_name() + " " + str(p.get_price()))


# Abstract Factory Method Design Pattern
# Entrypoint into main application
def abstract_factory_method():
    opel = OPELFactory()
    ford = FORDFactory()

    print("Creating OPEL")
    opel_car = BuildCar()
    opel_car.create_car(opel)
    opel_car.display_parts()

    print("\nCreating FORD")
    ford_car = BuildCar()
    ford_car.create_car(ford)
    ford_car.display_parts()


if __name__ == "__main__":
    abstract_factory_method()
