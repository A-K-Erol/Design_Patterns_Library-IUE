#include <iostream>
#include <vector>
using namespace std;


//============================================================================
//Name        : FactoryMethod.cpp
//
//The classes and/or objects participating in this pattern are:
//1. Product  (Engine,Transmission - Abstract)
//	 Defines the interface of objects the factory method creates
//2. ConcreteProduct  (OPEL_Engine, OPEL_Transmission)
//	 Implements the Product interface
//3. Creator  (CarCreator)
//	 Declares the factory method, which returns an object of type Product.
//	 Creator may also define a default implementation of the factory method
//	 that returns a default ConcreteProduct object.
//	 May call the factory method to create a Product object.
//4. ConcreteCreator (OPELCreator)
//	 Overrides the factory method to return an instance of a ConcreteProduct.
//============================================================================

// Top "Abstract Product" Part Class;
class Part{
public:
    virtual string displayName() = 0;
    virtual double getPrice() = 0;
};

// Engine base class
class Engine: public Part{
protected:
    double price{};
    string name;
public:
    double getPrice() override {return price;}
    string displayName() override {return name;}
};

//Transmission base class
class Transmission: public Part{
protected:
    double price{};
    string name;
public:
    double getPrice() override {return price;}
    string displayName() override {return name;}
};

//A 'ConcreteProduct' class

class OPEL_Engine : public Engine {
public:
    explicit OPEL_Engine(double p) {
        price = p;
        name = "OPEL Engine";
        cout << "OPEL Engine is created..." << endl;

    }
};

//A 'ConcreteProduct ' class
class OPEL_Transmission : public Transmission {
public:
    explicit OPEL_Transmission(double p) {
        price = p;
        name = "OPEL Transmission";
        cout << "OPEL Transmission is created..." << endl;

    }
};

//An 'Abstract Creator' class
//--> CarCreator

class CarCreator{   
    // Object creation is delegated to factory.
public:
    virtual Engine* createEngine() = 0;
    virtual Transmission* createTransmission() = 0;
    void createCar() {
        parts.push_back(createEngine());
        parts.push_back(createTransmission());
    }
    void displayParts() {
        cout << "\tListing Parts\n\t-------------" << endl;
        for (Part* partPtr: parts) { cout << "\t" << partPtr->displayName() << " " << partPtr->getPrice() << endl;}
    }

private:
    vector<Part *> parts;
};

//A 'ConcreteCreator' class ---> OPELCreator

class OPELCreator : public CarCreator {
    // Factory Method implementation
    // We are overriding the factory method
public:
    OPEL_Engine *createEngine() override {
        return new OPEL_Engine (25000.00);
    }
    OPEL_Transmission *createTransmission() override {
        return new OPEL_Transmission(10000.00);
    }
};

//Factory Method Design Pattern.
//Entry point into main application.
int main(){
    // Create an OPEL_car.
    CarCreator *creator;
    creator = new OPELCreator();
    cout << "Creating OPEL" << endl;
    creator->createCar();
    creator->displayParts();
}