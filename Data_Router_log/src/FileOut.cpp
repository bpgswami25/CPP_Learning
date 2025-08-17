#include "FileOut.hpp"
#include <cstring>

namespace dataRouter::Log{
    void FileLogOut::writeLog(char* msg)
    {
    std::ofstream outputFile(fileName,std::ios::app);
    size_t bufferSize = std::strlen(msg);

    if (outputFile.is_open()) {
        outputFile.write(msg, bufferSize);
        outputFile << '\n';
        outputFile.close();
       std::cout << "Successfully wrote to the file 'Log.txt'." << std::endl;
    } else {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }

    }
}