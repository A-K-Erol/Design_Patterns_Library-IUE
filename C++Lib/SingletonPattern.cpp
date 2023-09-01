#include <iostream>
#include <vector>
#include <mutex>
#include <random>
using namespace std;

//
//The classes and/or objects participating in this pattern are:
//1. Singleton   (LoadBalancer)
//		Defines an Instance operation that lets clients access its unique
//		instance. Instance is a class operation. Responsible for
//		creating and maintaining its own unique instance

//This is the "Singleton" class.

class LoadBalancer{
public:
    LoadBalancer* GetLoadBalancer(){
        if (instance == nullptr) {
            lock.lock();
            cout << "Acquired Lock\n";
            try{
                if (instance == nullptr){
                instance = new LoadBalancer();
                }
            }
            // for all errors, unlock and return. if successful, also unlock.
            catch (...){
                cout << "Released Lock with Exception\n";
                lock.unlock();
                return nullptr;
            }
            cout << "Released Lock\n";
            return instance;

        }
        return instance;
    }

    string getServer(){
        random_device randomDevice;
        mt19937 gen(randomDevice());
        uniform_int_distribution<> distribution(0, (int) servers.size() - 1);

        int rand = distribution(gen);
        return servers.at(rand);
    }

    LoadBalancer(){
        servers.emplace_back("Server I");
        servers.emplace_back("Server II");
        servers.emplace_back("Server III");
        servers.emplace_back("Server IV");
        servers.emplace_back("Server V");
    }


private:
    static LoadBalancer  *instance;
    vector<string> servers;
    static mutex lock;

};

//type declarations for static vars
LoadBalancer* LoadBalancer::instance = nullptr;
mutex LoadBalancer::lock;

int main(){
    // Three LoadBalancer* are created and set to point to the singleton instance
    LoadBalancer *lb1, *lb2, *lb3;

    lb1 = (new LoadBalancer())->GetLoadBalancer();
    lb2 = (new LoadBalancer())->GetLoadBalancer();
    lb3 = (new LoadBalancer())->GetLoadBalancer();

    //same instance?
    if (lb1 == lb2 && lb3 == lb2)
        cout << "Same Instance" << endl;
    else
        cout << "Different Instance" << endl;

    cout << "load balancer 1: <" << lb1 << ">" << endl;
    cout << "load balancer 2: <" << lb2 << ">" << endl;
    cout << "load balancer 3: <" << lb3 << ">" << endl;

    //All are the same instance. Use lb1 arbitrarily

    //Load Balance 15 server requests
    cout << "Generating 15 requests...." << endl;
    for (int i = 0; i < 15; i++)
        cout << lb1->getServer() << endl;

    return 0;
}
