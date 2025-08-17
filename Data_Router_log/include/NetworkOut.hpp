#include <iostream>
#include "Logout.hpp"

namespace dataRouter::Log{
    class NetworkLogOut : public LogOut{
        public:
        NetworkLogOut();
        ~NetworkLogOut();
        void writeLog(char* msg) override;
    };
}