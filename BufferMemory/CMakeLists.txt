cmake_minimum_required(VERSION 3.10)

project(SharedMemoryWrapper CXX)


add_library(shared_memory_lib SHARED src/SharedMemoryWrapper.cpp)


target_include_directories(shared_memory_lib PUBLIC include)

