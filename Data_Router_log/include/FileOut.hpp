#include <iostream>
#include "Logout.hpp"
#include <iostream>
#include <fstream> 
#include <string>

namespace dataRouter::Log{
    class FileLogOut : public LogOut{
        public:
        FileLogOut(){}
        ~FileLogOut(){}
        void writeLog(char* msg) override;
        private:
        std::string fileName{"Log.txt"};
    };
}