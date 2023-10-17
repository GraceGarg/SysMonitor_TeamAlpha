#pragma once

#include <string>

class Logger {
public:
    Logger(const std::string& filename);
    void logMessage(const std::string& message);
   bool createLogFileIfNotExists(const std::string& filename);

};
