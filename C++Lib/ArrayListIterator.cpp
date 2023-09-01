#include <iostream>
#include <iterator>
#include <utility>
#include <vector> // vectors are used instead of ArrayLists because ArrayLists are not supported in C++.
using namespace std;
//main function at bottom

//Item class from IteratorPattern.cpp;
class Item{
public:
    explicit Item(string name){ _name = move(name);}
    string getName() { return _name;};
private:
    string _name;
};

//prints all items in the collection;
void printAggregate(vector<Item>::iterator itr, vector<Item> aggregate) {
    cout << "Iterating over collection:" << endl;

    for (itr = aggregate.begin(); itr < aggregate.end();itr = next(itr, 1)){
        Item element = *itr;
        cout << element.getName() << endl;
    }
    cout << endl;
}

// prints all items in a collection in reverse order
void printAggregateBackwards(vector<Item>::iterator itr, vector<Item> aggregate) {
    cout << "Iterating over collection backwards:" << endl;
    for (itr = aggregate.end() - 1; itr > aggregate.begin() - 1; itr = prev(itr, 1)){
        Item element = *itr;
        cout << element.getName() << endl;
    }
    cout << endl;
}

int main(){

    vector<Item> aggregate; //create and initialize the aggregate
    aggregate.push_back(*new Item("Item 0"));
    aggregate.push_back(*new Item("Item 1"));
    aggregate.push_back(*new Item("Item 2"));
    aggregate.push_back(*new Item("Item 3"));
    aggregate.push_back(*new Item("Item 4"));
    aggregate.push_back(*new Item("Item 5"));
    aggregate.push_back(*new Item("Item 6"));
    aggregate.push_back(*new Item("Item 7"));
    aggregate.push_back(*new Item("Item 8"));

    //create iterators
    vector<Item>::iterator itr;
    vector<Item>::iterator itrBack;

    //print forwards, then backwards
    printAggregate(itr, aggregate);
    cout << endl;

    printAggregateBackwards(itrBack, aggregate);
    cout << endl;

    //print forwards without using iterator
    cout << "Manual Iteration:" << endl;
    for (Item it : aggregate){cout << it.getName() << endl;}
    reverse_iterator<vector<Item>::iterator> *test;
}