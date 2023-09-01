import abc
# The classes and/or objects participating in this pattern are:
# 1. Component   (DrawingElement)
# Declares the interface for objects in the composition. Implements
# default behavior for the interface common to all classes, as
# appropriate. declares an interface for accessing and managing its
# child components.
# 2. Leaf   (PrimitiveElement)
# represents leaf objects in the composition. A leaf has no children.
# Defines behavior for primitive objects in the composition.
# 3. Composite   (CompositeElement)
# defines behavior for components having children. Stores child
# components. Implements child-related operations in the Component interface.
# 4. Client  (CompositeApp)
# Manipulates objects in the composition through the Component interface.


# This is the Component, aka 'TreeNode'
class DrawingElement:
    @abc.abstractmethod
    def add(self, d):
        pass

    @abc.abstractmethod
    def remove(self, d):
        pass

    @abc.abstractmethod
    def display(self, indent):
        pass

    @abc.abstractmethod
    def get_name(self):
        pass


# This is 'Leaf'
class PrimitiveElement(DrawingElement):

    def __init__(self, name):
        self.__name = name

    def get_name(self):
        return self.__name

    def add(self, d):
        print("Cannot add to a PrimitiveElement.")

    def remove(self, d):
        print("Cannot remove from a PrimitiveElement.")

    def display(self, indent):
        for i in range(indent):
            print("-", end='')
        print(" " + self.__name)


# This is the 'Composite'
class CompositeElement(DrawingElement):

    def __init__(self, name):
        self.__name = name
        self.__elements = []

    def get_name(self):
        return self.__name

    def add(self, d):
        self.__elements.append(d)

    def remove(self, d):
        self.__elements.remove(d)

    def display(self, indent):
        for i in range(indent):
            print("-", end='')
        print("+ " + self.__name)

        # Display each child element on this node
        for j in range(len(self.__elements)):
            self.__elements[j].display(indent + 2)


# This is the client
def composite_pattern():
    # Create a tree structure
    root = CompositeElement("Picture")
    root.add(PrimitiveElement("Red Line"))
    root.add(PrimitiveElement("Blue Circle"))
    root.add(PrimitiveElement("Green Box"))

    comp = CompositeElement("Two Circles")
    comp.add(PrimitiveElement("Black Circle"))
    comp.add(PrimitiveElement("White Circle"))
    root.add(comp)

    # Add and remove a primitive element
    pe = PrimitiveElement("Yellow Line")
    root.add(pe)
    root.remove(pe)

    # Recursively display nodes
    root.display(1)


if __name__ == "__main__":
    composite_pattern()
