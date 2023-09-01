import abc
from abc import ABC


# Element (Element) defines an accept operation that takes visitor as argument
class Element:
    @abc.abstractmethod
    def accept(self, visitor):
        pass


# "Visitor" declares a Visit operation for each class of ConcreteElement in the
# object structure. The operation's name and signature identifies the
# class that sends the Visit request to the visitor. That lets the
# visitor determine the concrete class of the element being visited.
# Then the visitor can access the elements directly through its particular
# interface

class Visitor:
    # visit selects which 'protected' visit method to call based on the input type
    def visit(self, element):
        if type(element) == Clerk:
            self.visit_clerk(element)
        elif type(element) == Director:
            self.visit_director(element)
        elif type(element) == President:
            self.visit_president(element)
        else:
            return "Invalid Employee"

    @abc.abstractmethod
    def visit_clerk(self, clerk):
        pass

    @abc.abstractmethod
    def visit_director(self, director):
        pass

    @abc.abstractmethod
    def visit_president(self, president):
        pass


# Concrete Element (Employee)
# implements an accept operation that
# takes a visitor as an argument
class Employee(Element, ABC):
    # Constructor
    def __init__(self, name, income, vacation_days):
        self.__name = name
        self.__income = income
        self.__vacation_days = vacation_days

    def get_name(self):
        return self.__name

    def set_name(self, value):
        self.__name = value

    def get_income(self):
        return self.__income

    def set_income(self, value):
        self.__income = value

    def get_vacation_days(self):
        return self.__vacation_days

    def set_vacation_days(self, value):
        self.__vacation_days = value


class Clerk(Employee):
    def __init__(self, name, salary, vacation):
        super().__init__(name, salary, vacation)

    def accept(self, visitor):
        visitor.visit(self)


class Director(Employee):
    def __init__(self, name, salary, vacation):
        super().__init__(name, salary, vacation)

    def accept(self, visitor):
        visitor.visit(self)


class President(Employee):
    def __init__(self, name, salary, vacation):
        super().__init__(name, salary, vacation)

    def accept(self, visitor):
        visitor.visit(self)


# ObjectStructure can enumerate its elements and may provide a
# high-level interface to allow the visitor to visit its elements -
# either a Composite (pattern) or collection like a list or set

# ObjectStructure (Employees)
class Employees:
    def __init__(self):
        self.__employees = []

    def add(self, employee):
        self.__employees.append(employee)

    def remove(self, employee):
        self.__employees.remove(employee)

    def accept(self, visitor):
        # Set argument to something that
        # helps tell observers what happened
        for employee in self.__employees:
            employee.accept(visitor)


# ConcreteVisitors (IncomeVisitor, VacationVisitor)
#
# implements each operation declared by Visitor. Each operation implements
# a fragment of the algorithm defined for the corresponding class or object
# in the structure. ConcreteVisitor provides the context for the algorithm
# and stores its local state. This state often accumulates results during the
# traversal of the structure.


# "ConcreteVisitor 1"
class IncomeVisitor(Visitor):
    def visit_clerk(self, element):
        element.set_income(element.get_income() * 1.10)
        print(element.get_name() + "'s new income:")
        print(round(element.get_income()))

    def visit_director(self, element):
        element.set_income(element.get_income() * 1.50)
        print(element.get_name() + "'s new income:")
        print(round(element.get_income()))

    def visit_president(self, element):
        element.set_income(element.get_income() * 2.00)
        print(element.get_name() + "'s new income:")
        print(round(element.get_income()))


# ConcreteVisitor 2
class VacationVisitor(Visitor):
    def visit_clerk(self, element):
        element.set_vacation_days(element.get_vacation_days() + 3)
        print(element.get_name() + "'s new vacation days:")
        print(round(element.get_vacation_days()))

    def visit_director(self, element):
        element.set_vacation_days(element.get_vacation_days() + 5)
        print(element.get_name() + "'s new vacation days:")
        print(round(element.get_vacation_days()))

    def visit_president(self, element):
        element.set_vacation_days(element.get_vacation_days() + 7)
        print(element.get_name() + "'s new vacation days:")
        print(round(element.get_vacation_days()))


# client app
def visitor_pattern():
    # setup employee collection
    e = Employees()
    e.add(Clerk("Ahmet", 200000, 10))
    e.add(Director("Batuhan", 300000, 20))
    e.add(President("Cansu", 400000, 30))

    # employees are 'visited'
    e.accept(IncomeVisitor())
    e.accept(VacationVisitor())


if __name__ == "__main__":
    visitor_pattern()
