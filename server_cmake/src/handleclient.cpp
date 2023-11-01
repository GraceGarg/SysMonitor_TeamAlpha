#include <iostream>
#include <boost/asio.hpp>
#include <mysql_driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "handleclient.h"
#include "CSVWriter.h"
#include "DatabaseHandler.h"
namespace asio = boost::asio; 
//using namespace boost::asio;
using namespace std;
void handleClient(asio::ip::tcp::socket clientSocket, sql::Connection *dbConnection) {
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

            // Null-terminate the received data
            buffer[bytesRead] = '\0';
            
            // Extract the received data and split it into fields
            string receivedData(buffer);
            vector<string> fields;
            size_t start = 0, end = 0;
            while ((end = receivedData.find(" ", start)) != string::npos) {
                fields.push_back(receivedData.substr(start, end - start));
                start = end + 1;
            }
            fields.push_back(receivedData.substr(start)); // Add the last field

         // Write the received data as a row in the CSV file
         CSVWriter csvWriter("live_data.csv");
         csvWriter.writeData(fields);

            stringstream ss(buffer);
            vector<string> vec1;
            string str1;
            while (ss >> str1) {
                vec1.push_back(str1);
            }
            string macAddr = vec1[0];
            string sys_n = vec1[1];
            string date = vec1[2];
            string time = vec1[3];
            string ram = vec1[4];
            string cpu = vec1[5];
            string idle = vec1[6];
            string hdd = vec1[7];
            string netw = vec1[8];
	
         cout << macAddr << endl << sys_n << endl << date << endl << time << endl << ram << endl << cpu << endl << idle << endl << hdd << endl << netw<<endl;
            
           DatabaseHandler handler(dbConnection);
            // Check if the MAC address exists in 'mac_addresses' table
            int node_id = handler.getNodeID(macAddr);

            // If the MAC address does not exist, insert it and get the new node_id
            if (node_id == -1) {
                handler.insertMacAddress(macAddr,sys_n);
                node_id = handler.getNodeID(macAddr);
            }

            // Insert the received data into the 'client_data' table
            handler.insertClientData(node_id,ram,cpu,idle,hdd,netw);
           
            boost::asio::write(clientSocket, boost::asio::buffer("Successfully Send\0", 19));
        }
    } catch (std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        boost::asio::write(clientSocket, boost::asio::buffer("Error in sending info\0", 24));
    }
}

