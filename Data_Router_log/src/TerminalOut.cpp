#include "TerminalOut.hpp"

namespace dataRouter::Log {
    TerminalLogOut::TerminalLogOut() {}
    TerminalLogOut::~TerminalLogOut() {}
    void TerminalLogOut::writeLog(char* msg) {
        // Implementation for writing log to terminal
        std::cout << "Terminal Log: " << msg << std::endl;
    }
}