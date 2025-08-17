#include "ConfigManager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
namespace dataRouter::Config{
    configManager configManager::mInstance;

    configManager::configManager(){}

    configManager::~configManager(){}

    configManager& configManager::getInstance()
    {
        return  mInstance;
    }
    std::string configManager::getLogOutType()
    {
        return mTypeofLogOut;
    }

    void configManager::ReadconfigFile(std::string path){
        std::ifstream config_file(path);
        std::cout << "Reading config file from: " << path << std::endl;
        if (config_file.is_open()) {
            
        try {
        json config_data = json::parse(config_file);

        std::string app_name = config_data["name"];
        std::string app_version = config_data["version"];
        mTypeofLogOut = config_data["settings"]["typeofoutput"];

        } catch (const json::parse_error& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            //return 1;
        }
    }else{
        std::cerr << "Error: Could not open config.json" << std::endl;
    }

    }
    

}