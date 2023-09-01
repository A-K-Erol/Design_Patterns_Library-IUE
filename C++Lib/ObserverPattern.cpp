#include <iostream>
#include <utility>
#include <vector>
using namespace std;

//============================================================================
//Name        : ObserverPattern.cpp
//============================================================================
//The classes and/or objects participating in this pattern are:
//	1. Subject  (Stock)
//		. Knows its observers. Any number of Observer objects may observe a subject.
//	    . Provides an interface for attaching and detaching Observer objects.
//	2. ConcreteSubject  (IBM)
//	    . Stores state of interest to ConcreteObserver sends a notification to its.
//		. Observers when its state changes.
//	3. Observer  (Investor)
//   . Defines an updating interface for objects that should be notified
//     of changes in a subject.
//	4. ConcreteObserver  (Investor)
//   . Maintains a reference to a ConcreteSubject object
//   . Stores state that should stay consistent with the subject's
//   . Implements the Observer updating interface to keep its state
//     consistent with the subject's

//forward declarations
class Observer;
class Investor;
class Stock;


//'Observer'  ==> Abstract Observer.
class Observer{
public:
    virtual void Update(Stock *stock){};
};


//'ConcreteObserver' ==> Investor
class Investor : public Observer {
private:
    Stock *_stock{};
    string _investor_name;
    string _stock_name;   // Internal Observer state
    double _stock_price{};   // Internal Observer state

public:
    // Constructor
    explicit Investor(string name) {
        _investor_name = move(name);
    }
    void Update(Stock *stock) override;

    Stock* getStock() {return _stock;}
    void setStock(Stock *value) {_stock = value;}
    string getName() {return _investor_name;}
};


//'Subject' ==> Stock
class Stock{
public:
    Stock(string symbol, double price){
        _symbol = move(symbol);
        _price = price;
    }

    //Register the Observers
    void Attach (Investor *investor){
        investors.push_back(investor);
    }

    //Unregister from list of observers
    void Detach (Investor *investor){
        for (int i = 0; i < investors.size(); i++){
            if (investors.at(i)->getName() == investor->getName()) {
                investors.erase(investors.begin() + i);
                return;
            }
        }
    }

    void Notify() {
        // set argument to something that helps
        // tell the Observers what happened

        for (auto & investor : investors){
            investor->Update(this);
        }
    }

    string getSymbol() {return _symbol;}
    void setSymbol(string value) {_symbol = move(value);}
    double getPrice() {return _price;}
    virtual void setPrice(double value) = 0;
protected:
    string _symbol;
    double _price;
    vector<Investor *> investors;
};

void Investor::Update(Stock *stock) {
    _stock = stock;
    _stock_price = _stock->getPrice();
    _stock_name = _stock->getSymbol();
    cout << "Notified " << _investor_name << " of " << _stock_name << "'s "
         << "change to " << _stock_price << endl;

}
//'ConcreteSubject' ==> IBM
class IBM: public Stock {
    //Constructor
public:
    IBM (string symbol, double price) : Stock(move(symbol), price){}
    double getPrice() {return _price;}
    void setPrice (double value) override {
        // Whenever a change happens to _price, notify
        // observers.
        _price = value;
        Notify();
    }
};


//test application
int main(){
    //Create Investors
    auto *s = new Investor("Ahmet");
    auto *b = new Investor("Ayhan");

    // Create IBM stock and attach investors
    IBM *ibm = new IBM("IBM", 120.00);
    s->setStock(ibm);
    b->setStock(ibm);
    ibm->Attach(s);
    ibm->Attach(b);

    ibm->setPrice(120.10);
    ibm->setPrice(121.00);
    ibm->setPrice(120.50);
    ibm->setPrice(120.75);

    cout << "Removing Ayhan from notification list \n";
    ibm->Detach(b);
    ibm->setPrice(121);
    ibm->setPrice(122);
    ibm->setPrice(123);
    ibm->setPrice(124);
    ibm = nullptr;
    //Candidate for Garbage Collection
    //Danger !!!!!!!, we have a dangling reference in our observer.
    //Remember our "implementation issues"
    //discussion in the lecture.

    cout << s->getStock() << endl; //Reference still has a value


}