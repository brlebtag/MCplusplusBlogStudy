#include <iostream>
#include <atomic>
#include <thread>

class SpinLock
{
    std::atomic_flag flag;
public:
    SpinLock(): flag(ATOMIC_FLAG_INIT) {}

    void lock()
    {
        while (flag.test_and_set());
    }

    void unlock()
    {
        flag.clear();
    }
};

SpinLock spin;

void workOnResource(int id) {
    spin.lock();
    std::cout << "Thread" << id << std::endl;
    spin.unlock();
}

int main(int argc, char* argv[])
{
    std::thread t1(workOnResource, 1);
    std::thread t2(workOnResource, 2);
    t1.join();
    t2.join();
    return 0;
}