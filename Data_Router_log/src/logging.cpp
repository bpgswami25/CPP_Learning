#include "Logging.hpp"
#include <thread>
#include "FileOut.hpp"
#include "NetworkOut.hpp"
#include "TerminalOut.hpp"
#include "../../BufferMemory/include/SharedMemoryWrapper.hpp"
#include <algorithm>

namespace dataRouter::Log{
LogOut* logging::mlogOut = nullptr;
logging::logging()
{

}
logging::~logging()
{

}
void logging::init(std::string Type)
{
        if (Type == "File") {
            mlogOut = new FileLogOut();
        } else if (Type == "Terminal") {
            mlogOut = new TerminalLogOut();
        } else if (Type == "Network") {
               mlogOut = new NetworkLogOut();
        } else {
            
        }

}
void logging::LoggingOut()
{
     std::thread workerThread([]() {

        std::cout << "Hello from a new thread!" << std::endl;
        SharedMemoryWrapper::SharedMemory consumer_shm("/LogMem");
        while(true){
            try {
                char read_buffer[100];
                if(!consumer_shm.read(read_buffer, 100,sizeof(sem_t) )){
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }else{
                    if (!std::all_of(std::begin(read_buffer), std::end(read_buffer), [](char c){ return c == 0; })) {
                        mlogOut->writeLog(read_buffer);
                    }
                }
        
            } catch (const std::exception& e) {
                std::cout << "Exception in writing logs: "<<e.what() << std::endl;
            }
       }
    });
    workerThread.detach();
}

}