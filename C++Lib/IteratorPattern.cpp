#include <iostream>
#include <utility>
#include <vector> //vectors used instead of arraylists since C++ does not support arraylists
using namespace std;

//main function is at bottom

//Iterator pattern:
//
//Provide a way to access the elements of an aggregate object
//sequentially without exposing its underlying representation.
//
//The classes and/or objects participating in this pattern are:
//1. Aggregate  (AbstractAggregate)
//		defines an abstract class for operating on the aggregate
//2. Iterator  (AbstractIterator)
//		defines an abstract class for accessing and traversing elements.
//3. ConcreteIterator  (CollectionIterator)
//		implements the Iterator interface.
//		keeps track of the current position in the traversal of the aggregate.
//4. ConcreteAggregate  (Collection)
//		implements the aggregate class to return an instance of the proper ConcreteIterator

//

class Item{
public:
    explicit Item(string name){ _name = move(name);}
    explicit Item() {_name = nullptr;}

    string getName() { return _name;};
private:
    string _name;
};

//interface for iterator
class AbstractIterator{
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone () = 0;
    virtual Item CurrentItem() = 0;
};


//interface for accessing aggregate
class AbstractAggregate {
public:
    virtual void add(Item it) = 0;
    virtual int getCount() = 0;
    virtual Item get(int idx) = 0;
    virtual AbstractIterator* getIterator() = 0;
};
class CollectionIterator : public AbstractIterator {
public:
    void First() final {_current = 0;}
    void Next() final {_current ++;}
    Item CurrentItem() final {
        if (!IsDone())
            return _collection->get(_current);
        Item fail = *new Item();
        return fail;
    }
    bool IsDone() final {return _current >= _collection->getCount();}

    explicit CollectionIterator(AbstractAggregate *collection){
        _collection = collection;
    }
private:
    AbstractAggregate *_collection;
    int _current = 0;
};

class Collection : public AbstractAggregate {
private:
    vector<Item> _items;
public:

    void add(Item item) final { _items.push_back(item); }

    Item get(int idx) final { return _items.at(idx); }

    int getCount() final { return (int) _items.size(); }

    AbstractIterator* getIterator() final {
        AbstractIterator* itr;
        itr = new CollectionIterator(this);
        return itr;
    }
};

void printAggregate(AbstractIterator* i) {
    cout << "Iterating over collection:" << endl;
    for(i->First();  !i->IsDone(); i->Next()) {
        cout << i->CurrentItem().getName() << endl;
    }
    cout << endl;
}

int main(){
    // initializes Collection and Collection pointer aggregate
    AbstractAggregate *aggregate;
    aggregate = new Collection();

    aggregate->add(*new Item("Item 0"));
    aggregate->add(*new Item("Item 1"));
    aggregate->add(*new Item("Item 2"));
    aggregate->add(*new Item("Item 3"));
    aggregate->add(*new Item("Item 4"));
    aggregate->add(*new Item("Item 5"));
    aggregate->add(*new Item("Item 6"));
    aggregate->add(*new Item("Item 7"));
    aggregate->add(*new Item("Item 8"));

    //instantiates a CollectionIterator and a pointer named "iterator" to it using the interface AbstractIterator.
    AbstractIterator *iterator;
    iterator = aggregate->getIterator();
    printAggregate(iterator);
}
