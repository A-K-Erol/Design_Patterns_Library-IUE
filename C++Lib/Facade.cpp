#include <iostream>
using namespace std;

// The classes and/or objects participating in this pattern are:
// 1. Facade   (Mortgage)
//		- knows which subsystem classes are responsible for a request.
//		- delegates client requests to appropriate subsystem objects.
// 2. Subsystem classes   (Bank, Credit, Loan)
//		- implement subsystem functionality.
//		- handle work assigned by the Facade object.
//		- have no knowledge of the facade and keep no reference to it.


// Client Class "Customer"

class Customer{
private:
    string name;
public:
    string getName() {return name;}
    explicit Customer(string customer_name) {name = move(customer_name);}
};

// Subsystem Class 1. "Bank"
class Bank{
public:
    bool HasSufficientSavings(Customer customer, int amount){
        cout << "Check bank balance of " << customer.getName()
                        << " for the amount " << amount << endl;
        return true;
    }
};

// Subsystem Class 2. "Credit"
class Credit{
public:
    bool HasGoodCredit(Customer customer) {
        cout << "Check credit for " << customer.getName() << endl;
        return true;
    }
};

// Subsystem Class 3. "Loan"

class Loan {
public:
    bool HasNoBadLoans(Customer customer) {
        cout << "Check outstanding loans for " << customer.getName() << endl;
        return true;
    }
};

// Facade "Mortgage"
class Mortgage{
private:
    Bank *bank;
    Loan *loan;
    Credit *credit;
public:
    Mortgage() {
        bank = new Bank();
        loan = new Loan();
        credit = new Credit();
    }

    bool isEligible(Customer customer, int amount) {
        cout << customer.getName() << " applies for " << amount << "TL loan" << endl;
        bool eligible = true;

        //Check applicant creditworthiness
        if (!bank->HasSufficientSavings(customer, amount)){
            eligible = false;
        }
        else if (!loan->HasNoBadLoans(customer)) {
            eligible = false;
        }
        else if (!credit->HasGoodCredit(customer)) {
            eligible = false;
        }
        return eligible;
    }
};

int main(){
// Facade
Mortgage *mortgage;
mortgage = new Mortgage();

// Evaluate mortgage eligibility for customer
Customer *customer;
customer = new Customer("Ufuk Celikkan");
bool eligible = mortgage->isEligible(*customer, 100000);
cout << customer->getName() << " has been "
                << (eligible ? "approved." : "rejected.") << endl;
}
