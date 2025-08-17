#include <iostream>
#include<fstream>

namespace dataRouter::Config{
class configManager{
    
    public:
    static configManager& getInstance();
    std::string getLogOutType();
    void ReadconfigFile(std::string path);
    
    private:
    std::string mTypeofLogOut;
    static configManager mInstance;
    configManager();
    ~configManager();
    configManager(configManager &)= delete;
    configManager operator=(configManager &)= delete;


};

}
