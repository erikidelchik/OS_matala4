#include <iostream>
#include <memory>
#include <mutex>

using namespace std;

template <typename T>
class Singleton{

    static unique_ptr<T> instance; // unique ptr so that no other pointer can point to this instance
    static mutex mtx; //static because getInstance() is static

public:
    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getInstance() {
        mtx.lock();
        if (!instance) {
            instance.reset(new T());
        }
        mtx.unlock();
        return *instance;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;
};

// Initialize static members
template <typename T>
unique_ptr<T> Singleton<T>::instance = nullptr;

template <typename T>
mutex Singleton<T>::mtx;


int main(){
    int& a = Singleton<int>::getInstance();
    int& b = Singleton<int>::getInstance();

    cout<< &a<<endl;
    cout<< &b<<endl;
}

