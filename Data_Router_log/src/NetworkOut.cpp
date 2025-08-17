#include "NetworkOut.hpp"

namespace dataRouter::Log { 
    NetworkLogOut::NetworkLogOut() {}

    NetworkLogOut::~NetworkLogOut() {}

    void NetworkLogOut::writeLog(char* msg) {
        // Implementation for writing log to network
        // This is a placeholder; actual implementation will depend on network protocol and requirements
        std::cout << "Network Log: " << msg << std::endl;
    }
}