#include <iostream>
#include "Logout.hpp"

namespace dataRouter::Log{
    class TerminalLogOut : public LogOut{
        public:
        TerminalLogOut();
        ~TerminalLogOut();
        void writeLog(char* msg) override;
    };
}