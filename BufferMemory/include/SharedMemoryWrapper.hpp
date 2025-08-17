#include <string>
#include <stdexcept>
#include <iostream>
#include <stdexcept>
#include <sys/mman.h>   // For shm_open, mmap, munmap
#include <sys/stat.h>    // For mode constants
#include <fcntl.h>       // For O_CREAT, O_RDWR
#include <unistd.h>      // For ftruncate, close
#include <cstring>       // For memcpy
#include <semaphore.h>   // For sem_t, sem_open, sem_wait, sem_post

namespace SharedMemoryWrapper
{
    
class SharedMemory {
public:
    struct SharedMemoryData {
        sem_t semaphore;
        char buffer[1024]; // A simple buffer to hold data
    };
    // Constructor for the producer (creates shared memory)
    SharedMemory(const std::string& name, size_t size);

    // Constructor for the consumer (opens existing shared memory)
    SharedMemory(const std::string& name);

    // Destructor to clean up resources
    ~SharedMemory();

    // Writes data to shared memory (Producer API)
    void write(const void* data, size_t size, size_t offset = 0);

    // Reads data from shared memory (Consumer API)
    bool read(void* buffer, size_t size, size_t offset = 0);

    // Get a direct pointer to the shared memory region for advanced use
    void* get_data_ptr() const;

private:
    std::string m_name;
    size_t m_size;
    void* m_ptr;
    int m_shm_fd;
};
} // namespace SharedMemoryWrapper