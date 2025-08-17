cmake_minimum_required(VERSION 3.10)
project(Mock)
add_executable(Mock MockApp.cpp)
target_link_libraries(Mock PRIVATE shared_memory_lib)
