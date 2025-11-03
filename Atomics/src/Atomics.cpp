#include <iostream>
#include <atomic>

template<typename T>
T fetch_mul(std::atomic<T>& shared, T mult)
{
    T oldValue = shared.load();
    while (!shared.compare_exchange_strong(oldValue, oldValue * mult));
    return oldValue;
}

int main(int argc, char *argv[])
{
    std::atomic<int> myInit{5};
    std::cout << myInit << std::endl;
    fetch_mul(myInit, 5);
    std::cout << myInit << std::endl;
    return 0;
}