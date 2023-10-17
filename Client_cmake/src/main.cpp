#include "socketHandler.h"
#include "dataHandler.h"
#include "Logger.h"
#include "main.h"
int main() {
    // Create a socket for the client
    socketHandler& obj1 = socketHandler::getInstance();
    std::string serverIpAddress = obj1.serverAddress;
    int clientSocket = obj1.connectToServer();

    dataHandler obj2(serverIpAddress);
    Logger logobj("my_log.txt");

    // Create a loop to continuously send updates to the server
    while (true) {
        std::string clientData = obj2.fetchData();

        // Send the client data to the server
        send(clientSocket, clientData.c_str(), clientData.length(), 0);

        char buffer2[4096];

        // Receive server data
        ssize_t bytesRead = recv(clientSocket, buffer2, sizeof(buffer2), 0);
        if (bytesRead == -1) {
            logobj.logMessage("failure");
            perror("Error in receiving log");
            break; // Exit the loop on receive error
        } else {
            logobj.logMessage("success");
        }

        // Sleep for 5 seconds before sending the next update
        sleep(5);
    }

    close(clientSocket);
    return 0;
}
