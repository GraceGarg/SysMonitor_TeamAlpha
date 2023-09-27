#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>

// Function to handle a single client connection
void handleClient(int clientSocket) {
    char buffer[4096];
    while (true) {
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            // Client disconnected or an error occurred
            close(clientSocket);
            return;
        }
        
        // Print the received data to the server console
        buffer[bytesRead] = '\0'; // Null-terminate the received data
        std::cout << "Received Data from Client: " << buffer << std::endl;

        // Process data received from the client
        // (You can parse and handle the data as needed)

        // Send a response back to the client (if needed)
        // send(clientSocket, response_data, response_length, 0);
    }
    
    // Create a loop to collect data from the client periodically
        while (true) {
            char buffer[4096];

            // Receive client data
            ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead == -1) {
                perror("Error in recv");
                break; // Exit the loop on receive error
            }

            // Display the received client data
            std::cout << "Client Data: " << std::endl;
            std::cout.write(buffer, bytesRead) << std::endl;

            // Sleep for 5 seconds before sending the next update
            sleep(5);
        }
}


int main() {

  std::vector<std::thread> clientThreads; // Store client threads
 
     	
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Replace with your desired port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the server socket to the address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error in bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming client connections
    if (listen(serverSocket, 5) == -1) {
        perror("Error in listen");
        exit(EXIT_FAILURE);
    }
    
  

    std::cout << "Server is listening on port 12345..." << std::endl;

    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("Error in accept");
            continue;
        }
        
        // Create a new thread to handle the client connection
        clientThreads.emplace_back(handleClient, clientSocket);
    }

    // Wait for all client threads to finish
    for (std::thread &t : clientThreads) {
        t.join();
    }

    close(serverSocket);
    return 0;
}
