#include "Logger.h"
#include "main.h"

Logger::Logger(const std::string& filename) {
    bool status=createLogFileIfNotExists(filename);
}

void Logger::logMessage(const std::string& message) {
    ofstream logFile("my_log.txt", ios::app); // Open the log file in append mode

    if (logFile.is_open()) {

        logFile << message << std::endl; // Write the message to the log file

        logFile.close(); // Close the log file

    } else {

        cerr << "Failed to open log file." << std::endl;

    }
}

 bool Logger::createLogFileIfNotExists(const std::string& filename) {

    // Check if the file exists

    ifstream checkFile(filename);

    while (!checkFile) {

        // The file doesn't exist, so create it

        ofstream createFile(filename);

        if (createFile) {

            createFile << "Logs of data recieved at server:" <<std::endl;

            createFile.close();

            return true;

        }
        return false;

    }



    if(checkFile) {

        cout << "File '" << filename << "' already exists." << std::endl;

        return true;

    }

    }
