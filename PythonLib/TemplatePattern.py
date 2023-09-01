import abc
# ================================================================================
# Name: TemplatePattern.py
#
# The classes / objects participating in this pattern are:
# 1. AbstractClass (CheckBackground)
#   Defines abstract primitive operations that concrete subclasses define to
#   implement steps of an algorithm. The template method calls primitive
#   operations as well as operations defined in AbstractClass or any other objects
# 2. ConcreteClass (MortgageLoanApp, EquityLoanApp)
#   implements the primitive operations to carry out subclass-specific
#   steps of the algorithm
# =================================================================================


class Data:
    @staticmethod
    def get_income():
        return 50000

    @staticmethod
    def get_credit_score():
        return 650


# This is the AbstractClass class

class CheckBackground:
    def __init__(self, name):
        self._name = name
        self._status = None

    def get_name(self):
        return self._name

    # This is our template method
    def check(self):
        self._prepare_application()

        self._status = (self.check_bank() and self.check_credit() and self.check_stock()
                        and self.check_loan() and self.check_income())
        self._finalize_application(self._status)

    # These are our concrete template operations
    @staticmethod
    def _prepare_application():
        print("Prepared paperwork")

    @staticmethod
    def _finalize_application(status):
        if status:
            print("Application Accepted")
        else:
            print("Application Rejected")

    @abc.abstractmethod
    def check_bank(self):
        pass

    @abc.abstractmethod
    def check_credit(self):
        pass

    @abc.abstractmethod
    def check_loan(self):
        pass

    @abc.abstractmethod
    def check_stock(self):
        pass

    @abc.abstractmethod
    def check_income(self):
        pass


# Concrete MortgageLoanApp class which implements the
# primitive operations.

class MortgageLoanApp(CheckBackground):
    def __init__(self, name):
        super().__init__(name)

    # other methods
    def check_bank(self):
        # Check acct balance
        print("check bank...")
        return True

    def check_credit(self):
        # check score from 3 companies
        print("check credit...")
        print("GOOD" if Data.get_credit_score() > 700 else "BAD")
        return Data.get_credit_score() > 700

    def check_loan(self):
        # Check other loan info
        print("check other loan...")
        return True

    def check_stock(self):
        # Check how many stock values
        print("check stock values... ")
        return True

    def check_income(self):
        # checks how much a family makes
        print("check income...")
        return Data.get_income() >= 50000


# Concrete EquityLoanApp class which implements the primitive
# operations, check_income and check_credit differ from
# MortgageLoanApp's methods


class EquityLoanApp(CheckBackground):
    def __init__(self, name):
        super().__init__(name)

    # other methods
    def check_bank(self):
        # Check acct balance
        print("check bank...")
        return True

    def check_credit(self):
        # check score from 3 companies
        has_good_credit = (Data.get_credit_score() > 600)
        print("check credit...")
        print("GOOD" if has_good_credit else "BAD")
        return has_good_credit

    def check_loan(self):
        # Check other loan info
        print("check other loan...")
        return True

    def check_stock(self):
        # Check how many stock values
        print("check stock values... ")
        return True

    def check_income(self):
        # checks how much a family makes
        print("check income...")
        return Data.get_income() >= 40000


# Test Program
def template_method():
    p = MortgageLoanApp("Ahmet")
    print("Check client " + p.get_name() + "'s")
    print(" mortgage loan application. ")
    p.check()

    p = EquityLoanApp("Ahmet")
    print("Check client " + p.get_name() + "'s")
    print(" equity loan application. ")
    p.check()


if __name__ == "__main__":
    template_method()
