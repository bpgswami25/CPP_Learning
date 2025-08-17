#include "SharedMemoryWrapper.hpp"

namespace SharedMemoryWrapper {
    /**
     * @brief Constructor for the producer (creates or opens shared memory).
     * @param name The unique name of the shared memory object.
     * @param size The size of the shared memory object in bytes.
     */
    SharedMemory::SharedMemory(const std::string& name, size_t size) : m_name(name), m_size(size), m_ptr(nullptr) {
        // Open or create the shared memory object
        m_shm_fd = shm_open(m_name.c_str(), O_CREAT | O_RDWR, 0666);
        if (m_shm_fd == -1) {
            throw std::runtime_error("shm_open failed");
        }

        // Set the size of the shared memory
        if (ftruncate(m_shm_fd, m_size) == -1) {
            close(m_shm_fd);
            throw std::runtime_error("ftruncate failed");
        }

        // Map the shared memory object into the process's address space
        m_ptr = mmap(0, m_size, PROT_READ | PROT_WRITE, MAP_SHARED, m_shm_fd, 0);
        if (m_ptr == MAP_FAILED) {
            close(m_shm_fd);
            throw std::runtime_error("mmap failed");
        }

        // Initialize the semaphore for synchronization
        auto* data = static_cast<SharedMemoryData*>(m_ptr);
        if (sem_init(&data->semaphore, 1, 1) == -1) {
            // Cleanup on failure
            munmap(m_ptr, m_size);
            close(m_shm_fd);
            throw std::runtime_error("sem_init failed");
        }
    }

    /**
     * @brief Constructor for the consumer (opens existing shared memory).
     * @param name The unique name of the shared memory object to open.
     */
    SharedMemory::SharedMemory(const std::string& name) : m_name(name), m_size(0), m_ptr(nullptr) {
        // Open the shared memory object. We don't use O_CREAT here.
        m_shm_fd = shm_open(m_name.c_str(), O_RDWR, 0666);
        if (m_shm_fd == -1) {
            throw std::runtime_error("shm_open failed (consumer)");
        }
        
        // Use fstat to get the size of the existing shared memory object
        struct stat st;
        if (fstat(m_shm_fd, &st) == -1) {
            close(m_shm_fd);
            throw std::runtime_error("fstat failed");
        }
        m_size = st.st_size;

        // Map the shared memory object into the process's address space
        m_ptr = mmap(0, m_size, PROT_READ | PROT_WRITE, MAP_SHARED, m_shm_fd, 0);
        if (m_ptr == MAP_FAILED) {
            close(m_shm_fd);
            throw std::runtime_error("mmap failed (consumer)");
        }
    }

    /**
     * @brief Destructor to clean up resources.
     * Unmaps the memory and closes the file descriptor.
     */
    SharedMemory::~SharedMemory() {
        if (m_ptr) {
            munmap(m_ptr, m_size);
        }
        if (m_shm_fd != -1) {
            close(m_shm_fd);
        }
    }

    /**
     * @brief Writes data to the shared memory (Producer API).
     * This method is thread-safe and process-safe due to semaphore.
     * @param data A pointer to the data to be written.
     * @param size The size of the data to be written.
     * @param offset The offset from the start of the shared memory segment.
     */
    void SharedMemory::write(const void* data, size_t size, size_t offset) {
        if (!m_ptr) {
            throw std::runtime_error("Shared memory not initialized.");
        }
        if (offset + size > m_size) {
            throw std::out_of_range("Write operation exceeds shared memory size.");
        }

        auto* shm_data = static_cast<SharedMemoryData*>(m_ptr);

        // Lock the semaphore to ensure exclusive access
        if (sem_wait(&shm_data->semaphore) == -1) {
            throw std::runtime_error("Failed to lock semaphore.");
        }

        // Perform the write operation
        memcpy(static_cast<char*>(m_ptr) + offset, data, size);

        // Unlock the semaphore
        if (sem_post(&shm_data->semaphore) == -1) {
            // In a real application, you'd handle this more gracefully.
            std::cerr << "Failed to unlock semaphore. Possible deadlock." << std::endl;
        }
    }
    
    // Reads data from shared memory (Consumer API)
    bool SharedMemory::read(void* buffer, size_t size, size_t offset) {
        if (!m_ptr) {
            return false;
        }
        if (offset + size > m_size) {
            return false;
        }

        auto* shm_data = static_cast<SharedMemoryData*>(m_ptr);

        // Lock the semaphore to ensure exclusive access
        if (sem_wait(&shm_data->semaphore) == -1) {
            return false;
        }

        // Perform the read operation
        memcpy(buffer, static_cast<char*>(m_ptr) + offset, size);
        // Clear the read portion of memory
        memset(static_cast<char*>(m_ptr) + offset, 0, size);
        // Unlock the semaphore
        if (sem_post(&shm_data->semaphore) == -1) {
            std::cerr << "Failed to unlock semaphore. Possible deadlock." << std::endl;
            return false;
        }
        return true;
    }

    // Get a direct pointer to the shared memory region for advanced use
    void* SharedMemory::get_data_ptr() const {
        return m_ptr;
    }
    
    /*// Static method to clean up the shared memory object
    static void SharedMemory::cleanup(const std::string& name) {
        if (shm_unlink(name.c_str()) == -1) {
            perror("shm_unlink");
        }
    }*/

}

