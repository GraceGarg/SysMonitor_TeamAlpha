#pragma once

#include <string>

class socketHandler {
public:
    static socketHandler& getInstance();
    int connectToServer();
    std::string serverAddress;
    int serverPort;
private:
    
    socketHandler() { 
        // Constructor code here 
    } 

    // Private copy constructor and assignment operator to prevent copying 
    socketHandler(const socketHandler&);
    socketHandler& operator=(const socketHandler&) = delete;

    
    
};
