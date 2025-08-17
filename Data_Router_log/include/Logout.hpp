#ifndef DATAROUTER_LOG_LOGOUT_HPP
#define DATAROUTER_LOG_LOGOUT_HPP

#include <iostream>

namespace dataRouter::Log{
    class LogOut
    {
        public:
        LogOut(){}
        virtual ~LogOut(){}
        virtual void writeLog(char* msg) = 0;

    };
}
#endif