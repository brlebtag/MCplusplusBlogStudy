#include <iostream>
#include <atomic>
#include <thread>

// https://www.modernescpp.com/index.php/acquire-release-semantic/
class SpinLock
{
    std::atomic_flag flag;
public:
    SpinLock() : flag(ATOMIC_FLAG_INIT) {}

    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire));
    }

    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
};

SpinLock spin;

void workOnResource(int id)
{
    spin.lock();
    std::cout << "critical area: " << id << std::endl;
    spin.unlock();
}


int main(int argc, char *argv[])
{

    std::thread t1(workOnResource, 1);
    std::thread t2(workOnResource, 2);

    t1.join();
    t2.join();

    return 0;
}