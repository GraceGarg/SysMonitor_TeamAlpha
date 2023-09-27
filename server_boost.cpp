#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>

using namespace boost::asio;
using ip::tcp;

// Function to handle a single client connection
void handleClient(tcp::socket clientSocket) {
    try {
        char buffer[4096];
        
        
        while (true) {
            boost::system::error_code error;
            size_t bytesRead = clientSocket.read_some(boost::asio::buffer(buffer), error);
            if (error == boost::asio::error::eof) {
                // Client disconnected
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }
            
            // Print the received data to the server console
        buffer[bytesRead] = '\0'; // Null-terminate the received data
        std::cout << std::endl<< "Received Data from Client: " << buffer << std::endl;


            // Process data received from the client
            // (You can parse and handle the data as needed)

            // Send a response back to the client (if needed)
            // boost::asio::write(clientSocket, boost::asio::buffer(response_data, response_length));
        }
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    boost::asio::io_context ioContext;

    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 12345)); // Replace with the desired port

    std::vector<std::thread> clientThreads; // Store client threads

    while (true) {
        tcp::socket clientSocket(ioContext);
        acceptor.accept(clientSocket);
        
        std::cout << "Server is listening on port 12345..." << std::endl;

        // Create a new thread to handle the client connection
        clientThreads.emplace_back(handleClient, std::move(clientSocket));
    }

    // Wait for all client threads to finish
    for (std::thread &t : clientThreads) {
        t.join();
    }

    return 0;
}