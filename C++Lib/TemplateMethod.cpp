#include <iostream>
using namespace std;
//============================================================================
//Name        : TemplateMethod.cpp
//
//The classes and/or objects participating in this pattern are:
//1. AbstractClass  (CheckBackground)
//			Defines abstract primitive operations that concrete subclasses
//			define to implement steps of an algorithm implements a template
//			method defining the skeleton of an algorithm. The template method
//			calls primitive operations as well as operations defined in
//			AbstractClass or those of other objects.
//2. ConcreteClass  (MortgageLoanApp, EquityLoanApp )
//			implements the primitive operations ot carry out subclass-specific
//			steps of the algorithm
//============================================================================

class Data {
public:
    static int getIncome() {return 50000;}
    static int getCreditScore() {return 650;}
};

//This is the AbstractClass class.

class CheckBackground {
public:
    explicit CheckBackground(string name){_name = move(name);}
    string getName() {return _name;}
    //This is our template method.
    void check() {
        prepareApplication();
        bool status = checkBank() && checkCredit() && checkLoan()
                    && checkStock() && checkIncome();
        finalizeApplication(status);
    }

    // These are our concrete template operations.
protected:
    static void prepareApplication() {
        cout << "Prepared Paperwork" << endl;
    }
    static void finalizeApplication(bool status) {
        if (status){cout << "Application Accepted\n";}
        else {cout << "Application Rejected\n";}
    }
    // These are Primitive Operations which will be overridden
    // by the subclasses. They are all abstract.
    string _name;
    virtual bool checkBank() = 0;
    virtual bool checkCredit() = 0;
    virtual bool checkLoan() = 0;
    virtual bool checkIncome() = 0;
    virtual bool checkStock() = 0;
};

//Concrete MortgageLoanApp class which implements the
//primitive operations.
class MortgageLoanApp : public CheckBackground {
public:
    explicit MortgageLoanApp(string name) : CheckBackground(name) {_name = move(name);}
    //other methods
protected:
    bool checkBank() final {//check acct, balance
        cout << "check bank... \n";
        return true;
    }

    bool checkCredit() final { //check score from 3 companies
        int cScore = Data::getCreditScore();
        cout << "check credit... " << ((cScore > 700) ? "GOOD\n" : "BAD\n");
        return (cScore > 700);
    }

    bool checkLoan() final { // check other loan info
        cout << "check other loan..." << endl;
        return true;
    }

    bool checkStock() final { //check how many stock values
        cout << "check stock values..." << endl;
        return true;
    }

    bool checkIncome() final { //check how much they make
        cout << "check income..." << endl;
        return (Data::getIncome() >= 50000);
    }
};
//Concrete EquityLoanApp class which implements the
//primitive operations. checkIncome and checkCredit
//differs from MortgageLoanApp's corresponding
//methods.

class EquityLoanApp : public CheckBackground {
public:
    explicit EquityLoanApp(string name) : CheckBackground(name) {_name = move(name);}
protected:
    bool checkBank() final {//check acct, balance
        cout << "check bank... \n";
        return true;
    }

    bool checkCredit() final { //check score from 3 companies
        int cScore = Data::getCreditScore();
        cout << "check credit... " << ((cScore > 600) ? "GOOD\n" : "BAD\n");
        return (cScore > 600);
    }

    bool checkLoan() final { // check other loan info
        cout << "check other loan..." << endl;
        return true;
    }

    bool checkStock() final { //check how many stock values
        cout << "check stock values..." << endl;
        return true;
    }

    bool checkIncome() final { //check how much a family makes
        cout << "check income..." << endl;
        return (Data::getIncome() >= 40000);
    }

};

//This is our test program.
int main(){
    CheckBackground *p = new MortgageLoanApp("Ahmet");
    cout << "Check client " << p->getName() << " mortgage loan application" << endl;
    p->check();

    cout << endl;

    p = new EquityLoanApp("Ahmet");
    cout << "Check client " << p->getName() << " equity loan application" << endl;
    p->check();
}