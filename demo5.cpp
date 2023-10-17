#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <sstream>
#include <fstream>

 

using namespace std;
using namespace boost::asio;
using ip::tcp;

 /* // Function to write data to a CSV file
void writeDataToCSV(const std::string& filename, const std::string& data) {
    ofstream csvFile(filename, ios::app); // Open file in append mode
    if (csvFile.is_open()) {
        csvFile << data << std::endl;
        csvFile.close();
    } else {
        cerr << "Error opening CSV file for writing." << endl;
    }
}  */


	

	/*
	// Function to write data to a CSV file
void writeDataToCSV(const std::string& filename, const std::string& data, bool isHeader) {
    std::ofstream csvFile;
    if (isHeader) {
        csvFile.open(filename);  // Open in write mode to overwrite any existing file
    } else {
        csvFile.open(filename, std::ios::app);  // Open in append mode for data rows
    }
    
    if (csvFile.is_open()) {
        csvFile << data << std::endl;
        csvFile.close();
    } else {
        std::cerr << "Error opening CSV file for writing." << std::endl;
    }
}

 */
 
 // Function to write data to a CSV file
void writeDataToCSV(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream csvFile(filename, std::ios::app);
    if (csvFile.is_open()) {
        for (const std::string& field : data) {
            csvFile << field << ",";
        }
        csvFile << std::endl;
        csvFile.close();
    } else {
        std::cerr << "Error opening CSV file for writing." << std::endl;
    }
}

// Function to insert a new MAC address into the 'mac_addresses' table
int insertMacAddress(sql::Connection *dbConnection, const string &macAddr,const string &sys_n) {
    sql::PreparedStatement *pstmt;
    pstmt = dbConnection->prepareStatement("INSERT INTO mac_addresses (mac_address, System_Name) VALUES (?, ?)");
    pstmt->setString(1, macAddr);
    pstmt->setString(2, sys_n);
    int result = pstmt->executeUpdate();
    delete pstmt;
    return result;
}

 

// Function to get the node_id for a MAC address
int getNodeID(sql::Connection *dbConnection, const string &macAddr) {
    sql::Statement *stmt = dbConnection->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT node_id FROM mac_addresses WHERE mac_address = '" + macAddr + "'");
    int node_id = -1; // Default value if not found
    if (res->next()) {
        node_id = res->getInt("node_id");
    }
    delete res;
    delete stmt;
    return node_id;
}

 

// Function to handle a single client connection
void handleClient(tcp::socket clientSocket, sql::Connection *dbConnection) {
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
            writeDataToCSV("live_data.csv", fields);
 

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
	

 

            cout << macAddr << endl << sys_n << endl << date << endl << time << endl << ram << endl << cpu << endl << idle << endl << hdd << endl << netw;

 

            // Check if the MAC address exists in 'mac_addresses' table
            int node_id = getNodeID(dbConnection, macAddr);

 

            // If the MAC address does not exist, insert it and get the new node_id
            if (node_id == -1) {
                insertMacAddress(dbConnection, macAddr,sys_n);
                node_id = getNodeID(dbConnection, macAddr);
            }

 

            // Insert the received data into the 'client_data' table
            sql::PreparedStatement *pstmt;
            pstmt = dbConnection->prepareStatement("INSERT INTO client_Info (node_id, Recieved_Date, Recieved_Time, RAM_Usage, CPU_Utilization, Idle_Time, HDD_Utilization, Network_Stats) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
            //pstmt->setInt(1, id);
            pstmt->setInt(1, node_id);
            pstmt->setString(2, date);
            pstmt->setString(3, time);
            pstmt->setString(4, ram);
            pstmt->setString(5, cpu);
            pstmt->setString(6, idle);
            pstmt->setString(7, hdd);
            pstmt->setString(8, netw);
            pstmt->execute();
            delete pstmt;

 

            boost::asio::write(clientSocket, boost::asio::buffer("Successfully Send\0", 19));
        }
    } catch (exception &e) {
        cerr << "Error: " << e.what() << endl;
        boost::asio::write(clientSocket, boost::asio::buffer("Error in sending info\0", 24));
    }
}

 

int main() {
    boost::asio::io_context ioContext;
    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 12345));
    vector<thread> clientThreads;

	/* string dataToWrite = "mac_address,sys_n,date,time,ram,cpu,idle,hdd,netw";
	writeDataToCSV("live_data.csv", dataToWrite);
	 */
	 
	 /*
    // Sample header (column names)
    string header = "mac_address,sys_n,date,time,ram,cpu,idle,hdd,netw";
    
    // Call the function to write the header (isHeader = true)
    writeDataToCSV("live_data.csv", header, true);

    // Sample data row
    string dataRow = "macAddr,sys_n,date,time,ram,cpu,idle,hdd,netw";
    
    // Call the function to write the data row (isHeader = false)
    writeDataToCSV("live_data.csv", dataRow, false);
	
	*/

    // Initialize MySQL Connector/C++
    sql::mysql::MySQL_Driver *driver;
    driver = sql::mysql::get_mysql_driver_instance();
    sql::Connection *dbConnection;
    dbConnection = driver->connect("tcp://localhost:3306", "Project", "Project@123456789");
    cout << "Database is connected";
    dbConnection->setSchema("SystemInfo");
    
    
       
 

    while (true) {
        tcp::socket clientSocket(ioContext);
        acceptor.accept(clientSocket);
        cout << "Server is listening on port 12345..." << endl;

 

        // Create a new thread to handle the client connection
        clientThreads.emplace_back(handleClient, move(clientSocket), dbConnection);
    }

 

    // Wait for all client threads to finish
    for (thread &t : clientThreads) {
        t.join();
    }

 

    // Close the database connection when done
    delete dbConnection;

 

    return 0;
}
