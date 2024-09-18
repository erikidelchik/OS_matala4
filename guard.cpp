#include <iostream>
#include <mutex>

using namespace std;

class Guard{
    mutex& mtx;

public:
    Guard(mutex& m): mtx(m){
        mtx.lock();
    }

    ~Guard(){
        mtx.unlock();
    }
};


int main(){


	return 0;
}
