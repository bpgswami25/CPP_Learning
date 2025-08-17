cmake_minimum_required(VERSION 3.10)
project(DataRouterApp)

# First, define the executable target
add_executable(DataRouterApp
    src/ConfigManager.cpp 
    src/FileOut.cpp
    src/NetworkOut.cpp
    src/TerminalOut.cpp
    src/logging.cpp
    src/main.cpp
)

# Then, add include directories to the newly defined target
target_include_directories(DataRouterApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(DataRouterApp PRIVATE shared_memory_lib)
# Finally, add the subdirectory and link the library
#add_subdirectory(${CMAKE_SOURCE_DIR}/../BufferMemory ${CMAKE_BINARY_DIR}/BufferMemory)#
#target_link_libraries(DataRouterApp PRIVATE ${CMAKE_SOURCE_DIR}/../BufferMemory/build/libshared_memory_lib.so)