#include <iostream>
#include <sstream>
#include <vector>
#include <mutex> // contains lock
#include <random>
#include <thread>

using namespace std;

//The classes and/or objects participating in this pattern are:
//1. Singleton   (LoadBalancer)
//		Defines an Instance operation that lets clients access its unique
//		instance. Instance is a class operation. Responsible for
//		creating and maintaining its own unique instance

// function prototypes
string threadIDtoName(const string& id);
void MyRunnable(char type);

// singleton load balancer class
class LoadBalancer {
private:
    vector<string> servers;
    static mutex lock;
    static LoadBalancer *instance;
public:
    // Thread Safe Load Balancer with Double-Checked Locking
    LoadBalancer *GetLoadBalancer(){
        // prints thread name
        auto threadID = this_thread::get_id();
        stringstream ss;
        ss << threadID;
        string tName = threadIDtoName(ss.str());

        //check 1
        if (instance == nullptr){
            lock.lock();
            cout << tName << " acquired lock" << endl;
            try{ //check 2
                if (instance == nullptr){
                    instance = new LoadBalancer();
                }
            }
            catch (...){ //for all errors, unlock and return nullptr
                lock.unlock();
                cout << tName << " released lock" << endl;
                return nullptr;
            }
            lock.unlock(); // if there is no error, unlock anyway and return instance
            cout << tName << " released lock" << endl;
            return instance;
        }
        return instance; // no costly locking required if instance isn't null
    }

    LoadBalancer* GetLoadBalancerNoDoubleCheck(){

        // prints thread name
        auto threadID = this_thread::get_id();
        stringstream ss;
        ss << threadID;
        string tName = threadIDtoName(ss.str());

        // lock occurs regardless of whether instance exists
        lock.lock();
        cout << tName << " acquired lock" << endl;
        try{
            if (instance == nullptr){
                    instance = new LoadBalancer();
            }
        }
        catch (...){
            lock.unlock();
            cout << tName << " released lock" << endl;
            return nullptr;
            }
        lock.unlock();
        cout << tName << " released lock" << endl;
        return instance;
    }

    //simple LoadBalancer - returns a random server at an index between 0 and 4
    string getServer() {
        random_device randomDevice;
        mt19937 gen(randomDevice());
        uniform_int_distribution<> distribution(0, (int) servers.size() - 1);
        int rand = distribution(gen);
        return servers.at(rand);
    }

    LoadBalancer() {
        servers.emplace_back("Server I");
        servers.emplace_back("Server II");
        servers.emplace_back("Server III");
        servers.emplace_back("Server IV");
        servers.emplace_back("Server V");
    }

    static void initInstance() {instance = nullptr;}
};

// Maps the thread's identification number to a convenient name.
string threadIDtoName(const string& id) {
    if (id == "2" || id == "5") {return "Thread 1: ";}
    if (id == "3" || id == "6") {return "Thread 2: ";}
    if (id == "4" || id == "7") {return "Thread 3: ";}
    return "Unmapped Thread";
}

//Runnable Routine
void MyRunnable(char type){
    auto threadID = this_thread::get_id();
    stringstream ss;
    ss << threadID;
    string tName = threadIDtoName(ss.str());

    LoadBalancer *lb;
    if (type == 'D')
        lb = (new LoadBalancer)->GetLoadBalancer();
    if (type == 'N')
        lb = (new LoadBalancer)->GetLoadBalancerNoDoubleCheck();
    cout << tName << " load balancer <" << lb << ">" << endl;

}




// type declarations for static vars
LoadBalancer *LoadBalancer::instance;
mutex LoadBalancer::lock;

int main(){

    cout << "START NO DOUBLE CHECKED LOCKING" << endl;
    // We have to create a scenario in which threads are starting
    // sequentially in order show the tradeoffs of double-checking

    LoadBalancer::initInstance();
    thread t1(MyRunnable, 'N');
    t1.join();

    thread t2(MyRunnable, 'N');
    t2.join();

    thread t3(MyRunnable, 'N');
    t3.join();

    LoadBalancer::initInstance(); // resets instance
    // We have to create a scenario in which threads are starting sequentially
    // in order show the real advantage of double-checking
    cout << endl << "START DOUBLE CHECKED LOCKING" << endl;
    thread thr1(MyRunnable, 'D');
    thr1.join();

    thread thr2(MyRunnable, 'D');
    thr2.join();

    thread thr3(MyRunnable, 'D');
    thr3.join();
}
