#include <iostream>
#include "Logout.hpp"

namespace dataRouter::Log{
    class logging
    {
        public: 
        logging();
        ~logging();
        void init(std::string Type);
        void LoggingOut();


        private:
        static LogOut* mlogOut;

    };
}