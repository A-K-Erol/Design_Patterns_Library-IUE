from IteratorPattern import Item


class ListIterator:
    @staticmethod
    def print_aggregate(iterator):
        print("Iterating over collection: ")
        for i in iterator:
            print(i.get_name())


def main():
    aggregate = []
    for i in range(9):
        aggregate.append(Item("Item " + str(i)))

    # Iterate Forwards
    itr = iter(aggregate)  # Create Iterator for aggregate
    ListIterator.print_aggregate(itr)

    # Iterate backwards.
    rev_itr = reversed(aggregate)  # Create Backwards Iterator
    ListIterator.print_aggregate(rev_itr)  # Same print_aggregate function

    print("Iterating without iterator: ")
    for item in aggregate:
        print(item.get_name())


if __name__ == "__main__":
    main()
