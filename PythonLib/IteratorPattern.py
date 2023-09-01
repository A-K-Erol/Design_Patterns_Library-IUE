import abc
#
# Iterator pattern:
#
# Provide a way to access the elements of an aggregate object
# sequentially without exposing its underlying representation.
#
# The classes / objects participating in this pattern are
#
# 1. Iterator (Abstract Iterator)
#   defines an interface for accessing and traversing elements
# 2. ConcreteIterator (Iterator)
#   implements the Iterator interface.
#   keeps track of the current position in the traversal of the aggregate.
# 3. Aggregate (Abstract Collection)
#   defines an interface for creating an iterator object
# 4. ConcreteAggregate (Collection)
#   implements the Iterator creation interface
#   to return an instance of the proper ConcreteIterator


# Our concrete collection consists of Items
class Item:
    def __init__(self, name):
        self.__name = name

    def get_name(self):
        return self.__name


# This is the abstract "Iterator"
class AbstractIterator:
    @abc.abstractmethod
    def first(self):
        pass

    @abc.abstractmethod
    def next(self):
        pass

    @abc.abstractmethod
    def is_done(self):
        pass

    @abc.abstractmethod
    def current_item(self):
        pass


# This is the 'concrete' iterator for collection
class CollectionIterator(AbstractIterator):
    def __init__(self, collection):
        self.__collection = collection
        self.__current = 0

    def first(self):
        self.__current = 0

    def next(self):
        self.__current += 1

    def current_item(self):
        if self.is_done():
            return None
        else:
            return self.__collection.get(self.__current)

    def is_done(self):
        return self.__current >= self.__collection.get_count()


# This is the abstract "Aggregate"
class AbstractAggregate:
    @abc.abstractmethod
    def create_iterator(self):
        pass

    @abc.abstractmethod
    def add(self, item):  # Not needed for iteration
        pass

    @abc.abstractmethod
    def get_count(self):  # Needed for iteration
        pass

    @abc.abstractmethod
    def get(self, index):  # Needed for Iteration
        pass


# This is the concrete aggregate
class Collection(AbstractAggregate):
    def __init__(self):
        self.__items = []

    def create_iterator(self):
        return CollectionIterator(self)

    def get_count(self):
        return len(self.__items)

    def add(self, item):
        self.__items.append(item)

    def get(self, index):
        return self.__items[index]


# Main functions
def print_aggregate(itr):
    print("Iterating over collection: ")
    itr.first()
    while not itr.is_done():
        print(itr.current_item().get_name())
        itr.next()
    print("")


def iterator_pattern():
    # Create Aggregate
    aggregate = Collection()
    for i in range(9):
        aggregate.add(Item("Item " + str(i)))

    # Create Iterator
    iterator = aggregate.create_iterator()

    # traverse the aggregate
    print_aggregate(iterator)


if __name__ == "__main__":
    iterator_pattern()
