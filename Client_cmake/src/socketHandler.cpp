#include "socketHandler.h"
#include "main.h"

socketHandler& socketHandler::getInstance() {
    static socketHandler Instance;
    std::cout << "Enter Server Address" << std::endl;
    std::cin >> Instance.serverAddress;
    std::cout << "Enter Server Port" << std::endl;
    std::cin >> Instance.serverPort;
    return Instance;
}

int socketHandler::connectToServer() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 
        if (clientSocket == -1) { 
            perror("Error in socket"); 
            exit(EXIT_FAILURE); 
        } 

        // Define the server address and port 
        struct sockaddr_in serverAddr; 
        serverAddr.sin_family = AF_INET; 
        serverAddr.sin_port = htons(serverPort); // Replace with the server's port 
        serverAddr.sin_addr.s_addr = inet_addr(serverAddress.c_str()); // Replace with the server's IP address 

        // Connect to the server 
        if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) { 
            perror("Error in connect"); 
            exit(EXIT_FAILURE); 
        } 
        return clientSocket; 
}



    