#include <iostream>
#include <vector>
using namespace std;


//=======================================================================
//Name        : AbstractFactory.cpp
// 1. AbstractFactory  ( CarFactory )
//	  Declares an interface for operations that create abstract products
// 2. ConcreteFactory  (OPELFactory,FordFactory)
//	  Implements the operations to create concrete product objects
// 3. AbstractProduct   (Part, Engine, Transmission)
//	  Declares an interface for a type of product object
// 4. Product  (OPEL_Engine, OPEL_Transmission,
//				 FORD_Engine, FORD_Transmission.)
//	  Defines a product object to be created by the corresponding
//    concrete factory implements the AbstractProduct interface
// 5. Client  (BuildCar)
//	  Uses interfaces declared by AbstractFactory and AbstractProduct
//    classes
//=======================================================================



// Top "Abstract Product" Part Class;
class Part{
public:
    virtual string displayName() = 0;
    virtual double getPrice() = 0;
};

// A 'Abstract Product A' base class
class Engine: public Part{
protected:
    double price{};
    string name;
public:
    double getPrice() override {return price;}
    string displayName() override {return name;}
};


//A 'ConcreteProduct A1' class
class OPEL_Engine : public Engine {
public:
    explicit OPEL_Engine(double p) {
        price = p;
        name = "OPEL Engine";
        cout << "OPEL Engine is created..." << endl;

    }
};


//A 'ConcreteProduct A2' class
class FORD_Engine : public Engine {
public:
    explicit FORD_Engine(double p) {
        price = p;
        name = "FORD Engine";
        cout << "FORD Engine is created..." << endl;

    }
};

//A 'Abstract Product A' class
class Transmission: public Part{
protected:
    double price{};
    string name;
public:
    double getPrice() override {return price;}
    string displayName() override {return name;}
};

//A 'ConcreteProduct B1' class
class OPEL_Transmission : public Transmission {
public:
    explicit OPEL_Transmission(double p) {
        price = p;
        name = "OPEL Transmission";
        cout << "OPEL Transmission is created..." << endl;

    }
};

//A 'ConcreteProduct B2' class
class FORD_Transmission : public Transmission {
public:
    explicit FORD_Transmission(double p) {
        price = p;
        name = "FORD Transmission";
        cout << "FORD Transmission is created..." << endl;

    }
};

//An 'Abstract Factory' class
class CarFactory{
public:
    virtual Engine *createEngine() = 0;
    virtual Transmission *createTransmission() = 0;
};

//A 'Concrete Factory' class
class OPELFactory : public CarFactory {
public:
    OPEL_Engine *createEngine() override {
        return new OPEL_Engine (25000.00);
    }
    OPEL_Transmission *createTransmission() override {
        return new OPEL_Transmission(10000.00);
    }
};

//Another 'Concrete Factory' class
class FORDFactory : public CarFactory {
public:
    FORD_Engine *createEngine() override {
        return new FORD_Engine (20000.00);
    }
    FORD_Transmission *createTransmission() override {
        return new FORD_Transmission(12000.00);
    }
};

//The 'Client'.
class BuildCar{
    // Object creation is delegated to factory.
public:
    void createCar(CarFactory *factory){
        parts.push_back(factory->createEngine());
        parts.push_back(factory->createTransmission());
    }

    void displayParts() {
        cout << "\tListing Parts\n\t-------------" << endl;
        for (Part* partPtr: parts) { cout << "\t" << partPtr->displayName() << " " << partPtr->getPrice() << endl;}
        cout << endl;
    }
private:
    vector<Part *> parts;
};

//Abstract Factory Method Design Pattern.
//Entry point into main application.
int main(){
    //Create Factories
    CarFactory *OPEL;
    OPEL = new OPELFactory();

    CarFactory *FORD;
    FORD = new FORDFactory();

    BuildCar *car;
    car = new BuildCar();
    cout << "Creating OPEL" << endl;
    car->createCar(OPEL);
    car->displayParts();

    car = new BuildCar();
    cout << "Creating FORD" << endl;
    car->createCar(FORD);
    car->displayParts();
}
