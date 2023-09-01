#include <iostream>
#include <utility>
#include <vector>
using namespace std;

//forward declarations:
class Element;
class Employee;
class Clerk;
class Director;
class President;
class Visitor;

// Element  (Element)
// defines an Accept operation that takes a visitor
// as an argument.
class Element{
public:
    virtual void Accept(Visitor* visitor) = 0;
};

//ConcreteElement  (Employee)
//implements an Accept operation that
//takes a visitor as an argument

class Employee : public Element{
private:
    string _name;
    double _income;
    int _vacationDays;
public:
    //Constructor
    Employee(string name, double income, int vacationDays){
        _name = move(name);
        _income = income;
        _vacationDays = vacationDays;
    }

    //Access Functions
    string getName() {return _name;}
    void setName(string value) {_name = move(value);}
    double getIncome() const {return _income;}
    void setIncome(double value) {_income = value;}
    int getVacationDays() const {return _vacationDays;}
    void setVacationDays(int value) {_vacationDays = value;}
};


//"Visitor" declares a Visit operation for each class of ConcreteElement in the
//object structure. The operation's name and signature identifies the
//class that sends the Visit request to the visitor. That lets the
//visitor determine the concrete class of the element being visited.
//Then the visitor can access the elements directly through its particular
//interface
//
//"Visitor"
class Visitor {
public:
    virtual void Visit(Clerk element) = 0;

    virtual void Visit(Director element) = 0;

    virtual void Visit(President element) = 0;
};

class Clerk : public Employee {
public:
    Clerk(string name, int salary, int vacation) : Employee(move(name), salary, vacation) {}
    void Accept(Visitor *visitor) final {visitor->Visit(*this);};
};

class Director : public Employee {
public:
    Director(string name, int salary, int vacation) : Employee(move(name), salary, vacation) {}
    void Accept(Visitor *visitor) final {visitor->Visit(*this);};
};

class President : public Employee {
public:
    President(string name, int salary, int vacation) : Employee(move(name), salary, vacation) {}
    void Accept(Visitor *visitor) final {visitor->Visit(*this);};
};


// ObjectStructure can enumerate its elements  may provide a
// high-level interface to allow the visitor to visit its elements
// may either be a Composite (pattern) or a collection such as a
// list or a set
//
// ObjectStructure  (Employees)
class Employees{
public:
    void Add(Employee *employee) {employees.push_back(employee);}
    void Remove(Employee *employee){
        for (int i = 0; i < employees.size(); i++) {
            if (employees.at(i)->getName() == employee->getName()) {
                employees.erase(employees.begin() + i);
                return;
            }
        }
    }
    void Accept(Visitor *visitor){
        // set argument to something that helps
        // tell the Observers what happened
        for (auto & employee : employees){
            employee->Accept(visitor);
        }
    }
private:
    vector<Employee *> employees;
};

// ConcreteVisitors (IncomeVisitor, VacationVisitor)
// implements each operation declared by Visitor. Each operation implements
// a fragment of the algorithm defined for the corresponding class or object
// in the structure. ConcreteVisitor provides the context for the algorithm
// and stores its local state. This state often accumulates results during
// the traversal of the structure.
//
// "ConcreteVisitor 1"

class IncomeVisitor : public Visitor {
public:
    void Visit(Clerk element) final {
        element.setIncome(element.getIncome() * 1.1);
        cout << element.getName() << "'s new income: ";
        cout << element.getIncome() << endl;
    }
    void Visit(Director element) final {
        element.setIncome(element.getIncome() * 1.50);
        cout << element.getName() << "'s new income: ";
        cout << element.getIncome() << endl;
    }
    void Visit(President element) final {
        element.setIncome(element.getIncome() * 2.0);
        cout << element.getName() << "'s new income: ";
        cout << element.getIncome() << endl;
    }
};

// "ConcreteVisitor 2"

class VacationVisitor : public Visitor {
public:
    void Visit(Clerk element) final {
        //Provide 3 extra vacation days
        element.setVacationDays(element.getVacationDays() + 3);
        cout << element.getName() << "'s new vacation days: ";
        cout << element.getVacationDays() << endl;
    }

    void Visit(Director element) final {
        //Provide 5 extra vacation days
        element.setVacationDays(element.getVacationDays() + 5);
        cout << element.getName() << "'s new vacation days: ";
        cout << element.getVacationDays() << endl;
    }

    void Visit(President element) final {
        //Provide 7 extra vacation days
        element.setVacationDays(element.getVacationDays() + 7);
        cout << element.getName() << "'s new vacation days: ";
        cout << element.getVacationDays() << endl;
    }
};

int main(){
    //Setup Employee Collection
    auto *e = new Employees();
    e->Add(new Clerk("Ajda Pekkan", 200000, 10));
    e->Add(new Director("Tarkan", 300000, 20));
    e->Add(new President("Sertab Erener", 400000, 30));

    //Employees are 'visited'
    e->Accept(new IncomeVisitor());
    e->Accept(new VacationVisitor());
}
