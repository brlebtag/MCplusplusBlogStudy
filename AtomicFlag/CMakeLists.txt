cmake_minimum_required(VERSION 3.10)

project(AtomicFlag)

add_executable(${PROJECT_NAME}_SpinLock src/SpinLock.cpp)

add_executable(${PROJECT_NAME}_Mutex src/Mutex.cpp)