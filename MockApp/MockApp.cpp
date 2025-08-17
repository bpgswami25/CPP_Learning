#include <iostream>
#include "../BufferMemory/include/SharedMemoryWrapper.hpp"
#include <thread>


int main() {
    const std::string SHM_NAME = "/LogMem";
        SharedMemoryWrapper::SharedMemory producer_shm(SHM_NAME, 1000);
        std::cout << "Producer: Shared memory created and mapped." << std::endl;
        int cnt = 0;
        while (true)
        {
        cnt++;
        std::string message = "Hello from the Mock APP! : "+ std::to_string(cnt);
        producer_shm.write(message.c_str(), message.size() + 1, sizeof(sem_t)); // Offset past the semaphore
        std::cout << "Producer: Wrote message: '" << message << "'" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for a while before writing again
        }
        
}