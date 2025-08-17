#include <iostream>
#include "../BufferMemory/include/SharedMemoryWrapper.hpp"


int main() {
    const std::string SHM_NAME = "/LogMem";
        SharedMemoryWrapper::SharedMemory producer_shm(SHM_NAME, 1000);
        std::cout << "Producer: Shared memory created and mapped." << std::endl;

        // Step 2: Write a message to the shared memory using the `write` method
        std::string message = "Hello from the Mock APP!";
        producer_shm.write(message.c_str(), message.size() + 1, sizeof(sem_t)); // Offset past the semaphore
        std::cout << "Producer: Wrote message: '" << message << "'" << std::endl;
}