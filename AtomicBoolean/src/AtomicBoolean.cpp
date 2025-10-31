#include <iostream>
#include <condition_variable>
#include <thread>
#include <vector>

std::vector<int> mySharedWork;
std::mutex mutex_;
std::condition_variable condVar;

bool dataReady;

void waitingForWork()
{
    std::cout << "Waiting " << std::endl;
    
    // condition_variable requires unique_lock instead of lock_guard.
    std::unique_lock<std::mutex> lck(mutex_);
    condVar.wait(lck, []{ return dataReady; });
    mySharedWork[1] = 2;

    std::cout << "Work done " << std::endl;
}

void setDataReady()
{
    mySharedWork = {1, 0, 3};
    {
        std::lock_guard<std::mutex> lck(mutex_);
        dataReady = true;
    }
    
    std::cout << "Data prepared" << std::endl;
    
    condVar.notify_one();
}

int main(int argc, char* argv[])
{
    std::cout << std::endl;

    std::thread t1{waitingForWork};
    std::thread t2{setDataReady};

    t1.join();
    t2.join();

    if (mySharedWork.size() > 0)
    {
        std::cout << mySharedWork[0];
    }

    for (int i = 1; i < mySharedWork.size(); i++)
        std::cout << ", " << mySharedWork[i];

    std::cout << std::endl;

    return 0;
}