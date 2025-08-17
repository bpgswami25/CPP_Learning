#include <iostream>
#include "Logging.hpp"
#include "ConfigManager.hpp"
#include <thread>

int main(){
    std::cout << "Data Router Log Application Started" << std::endl;
    dataRouter::Config::configManager::getInstance().ReadconfigFile("/workspaces/CPP_Learning/Data_Router_log/etc/config.json");
    std::string logType = dataRouter::Config::configManager::getInstance().getLogOutType();
    dataRouter::Log::logging log;
    std::cout << "Logging initialized with type: " << logType << std::endl;
    log.init(logType);
    log.LoggingOut();
    std::cout << "Data Router Log Application is running..." << std::endl;
    // Keep the application running to allow logging
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Sleep to keep the main thread alive
    }

    return 0;
}