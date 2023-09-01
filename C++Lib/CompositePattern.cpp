#include <iostream>
#include <vector>
using namespace std;

// The classes and/or objects participating in this pattern are:
// 1. Component   (DrawingElement)
//		Declares the interface for objects in the composition. Implements
//      default behavior for the interface common to all classes, as
//      appropriate. declares an interface for accessing and managing its
//		child components.
// 2. Leaf   (PrimitiveElement)
//		represents leaf objects in the composition. A leaf has no children.
//	    Defines behavior for primitive objects in the composition.
// 3. Composite   (CompositeElement)
//		defines behavior for components having children. Stores child
//		components. Implements child-related operations in the Component interface.
// 4. Client  (CompositeApp)
//		Manipulates objects in the composition through the Component interface.


// This is the "Component". (i.e tree node.)
class DrawingElement {
public:
    virtual void Add(DrawingElement* d) = 0;
    virtual void Remove(DrawingElement* d) = 0;
    virtual void Display(int indent) = 0;
    virtual string getName() = 0;
};

//This is the "Leaf".
class PrimitiveElement : public DrawingElement{
private:
    string name;
public:
    string getName() final {return name;}
    explicit PrimitiveElement(string name) {this->name = move(name);}
    void Add(DrawingElement* c) final {cout << "Cannot add to a PrimitiveElement." << endl;}
    void Remove(DrawingElement* c) final {cout << "Cannot remove from a PrimitiveElement." << endl;}
    void Display(int indent) final {
        for (int i = 1; i <= indent; i++){
            cout << "-";
        }
        cout << " " + name << endl;
    }
};


// This is the "Composite"
class CompositeElement : public DrawingElement{
private:
    string name;
    vector<DrawingElement *> elements;
public:
    string getName() override {return name;}
    explicit CompositeElement(string name) {this->name = move(name);}
    void Add(DrawingElement *d) override {elements.push_back(d);}
    void Remove(DrawingElement *d) override {
        for (int i = 0; i < elements.size(); i++){
            if (elements.at(i)->getName() == d->getName()){
                elements.erase(elements.begin()+i);
                elements.shrink_to_fit();
            }
        }
    }

    void Display(int indent) override {
        for (int i = 1; i <= indent; i++){
            cout << "-";
        }
        cout << "+ " << getName() << endl;

        for (auto & element : elements){
            element->Display(indent + 2);
        }

    }
};

//This is the "client"
int main(){

    //creates a tree structure
    DrawingElement *root;
    root = new CompositeElement("Picture");
    root->Add(new PrimitiveElement("Red Line"));
    root->Add(new PrimitiveElement("Blue Circle"));
    root->Add(new PrimitiveElement("Green Box"));

    DrawingElement *comp;
    comp = new CompositeElement("Two Circles");
    comp->Add(new PrimitiveElement("Black Circle"));
    comp->Add(new PrimitiveElement("White Circle"));
    root->Add(comp);

    // add and remove a PrimitiveElement
    DrawingElement *pe;
    pe = new PrimitiveElement("Yellow Line");
    pe->Add(new PrimitiveElement ("Red Line"));
    root->Add(pe);
    root->Remove(pe);

    // recursively display nodes
    root->Display(1);
}
