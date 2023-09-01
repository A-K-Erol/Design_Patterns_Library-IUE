# The classes / objects participating in this pattern are:
# 1. Facade (Mortgage)
#   - knows which subsystem classes are responsible for a request
#   - delegates client requests to appropriate subsystem request
# 2. Subsystem classes (Bank, Credit, Loan)
#   - implement subsystem functionality
#   - handle work assigned by the Facade object
#   - have no knowledge of the facade and keep no reference to it.


# Client class
class Customer:
    def __init__(self, name):
        self.__name = name

    def get_name(self):
        return self.__name


# Subsystem Class 1: "Bank"
class Bank:
    def has_sufficient_savings(self, customer, amount):
        print("Check bank balance of " + customer.get_name() + " for the amount " + str(amount))
        return True


# Subsystem Class 2: "Credit"
class Credit:
    def has_good_credit(self, customer):
        print("Check credit for " + customer.get_name())
        return True


# Subsystem Class 3: "Loan"
class Loan:
    def has_no_bad_loans(self, customer):
        print("Check outstanding loans for " + customer.get_name())
        return True


# Facade: "Mortgage"
class Mortgage:
    def __init__(self):
        self.bank = Bank()
        self.loan = Loan()
        self.credit = Credit()

    def is_eligible(self, cust, amount):
        print(cust.get_name() + " applies for " + str(amount) + "TL loan")
        eligible = True

        # check creditworthiness of applicant
        if not self.bank.has_sufficient_savings(cust, amount):
            eligible = False

        elif not self.loan.has_no_bad_loans(cust):
            eligible = False

        elif not self.credit.has_good_credit(cust):
            eligible = False

        return eligible


# main client
def facade():
    # Facade
    mortgage = Mortgage()

    # Evaluate mortgage eligibility for customer
    customer = Customer("Ufuk Celikkan")

    # Since Dr. Ufuk is such a great teacher, he should
    # automatically be accepted. Let's verify:
    eligible = mortgage.is_eligible(customer, 100000)
    print(customer.get_name() + " has been " + ("approved" if eligible else "rejected"))


if __name__ == "__main__":
    facade()
