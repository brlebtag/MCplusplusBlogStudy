#include <iostream>
#include <atomic>
#include <string>
#include <thread>

using namespace std;

std::string work;
std::atomic<bool> ready{false};

void consumer()
{
    while (!ready.load());
    std::cout << work << std::endl;
}

void producer()
{
    work = "done";
    ready = true;
}

int main(int argc, char* argv[])
{
    std::thread prod(producer);
    std::thread con(consumer);
    prod.join();
    con.join();
    std::cout << "Finished!" << std::endl;
    return 0;
}