#pragma once

#include <string>

class dataHandler {
public:
std::string serverAddress;
    dataHandler(const std::string& ipAddress);
    std::string fetchData();
    std::string clientData;
    
private:
    
std::string systemId;
    std::string systemName;
        std::string networkStatus;
        std::string ramUsage;
        std::string hddUtilization;
       std::string idleTime;
        std::string cpuUtilization;

    std::string getMacAddress();
    std::string getSystemName();
    std::string getRamUsage();
    bool isNetworkConnected(const std::string& ip);
    std::string getHddUtilization();
    std::string getIdleTime();
    std::string getCpuUtilization();
    std::string getCurrentDateTimeAsString();
};
