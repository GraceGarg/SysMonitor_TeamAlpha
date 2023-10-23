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

 std::vector<std::string> whitelist = {

    "192.168.1.100", // Add your whitelisted IP addresses here

    "192.168.1.101",
    "192.168.43.11"

};

 

// Function to check if the client's IP address is whitelisted

bool isWhitelisted(const std::string& clientAddress) {

    for (const std::string& address : whitelist) {

        if (clientAddress == address) {

            return true;

        }

    }

    return false;

}
 
 class DatabaseConnector
 {
 public :
 
  sql::Connection* dbConnection;
 DatabaseConnector(const std::string& server_,const std::string& username_, const std::string& password_)
        : server(server_), username(username_), password(password_) {
        driver= sql::mysql::get_mysql_driver_instance();
    }
    
    bool connectToDatabase() {
        try {
            dbConnection = driver->connect(server, username, password);
            return true;  // Connection successful
        } catch (sql::SQLException& e) {
            
            return false;  // Connection failed
        }
    }
    
    void disconnectFromDatabase() {
        if (dbConnection) {
            dbConnection->close();
            delete dbConnection;
        }
    }
   
    private:
    sql::mysql::MySQL_Driver* driver;
    std::string server;
    std::string username;
    std::string password;
    
 };
 
 
 class DbStructure
 {
 private:
 sql::Connection* dbConnection;
 // Private constructor to prevent external instantiation
    DbStructure(sql::Connection* dbConnection) : dbConnection(dbConnection) {}

    // Private copy constructor and assignment operator to prevent copying
    DbStructure(const DbStructure&) = delete;
    DbStructure& operator=(const DbStructure&) = delete;
 public:
 static DbStructure& getInstance(sql::Connection *dbconnection)
 {
 static DbStructure Instance(dbconnection);
 Instance.dbConnection=dbconnection;
 return Instance;
 }
 void CreateDb ()
 {
 try{
  // Create a new database if it doesn't exist
            sql::Statement *createDbStmt =dbConnection->createStatement();
            createDbStmt->execute("CREATE DATABASE IF NOT EXISTS SystemInfo");
            delete createDbStmt;

            // Use the created database
           dbConnection->setSchema("SystemInfo");

 }
  catch (sql::SQLException &e) {
            std::cerr << "MySQL Error: " << e.what() << std::endl;
            
        }
  }
  void CreateTables()
  {
  try{
  
         // Create the 'mac_addresses' table
            sql::Statement *stmt =dbConnection->createStatement();
           stmt->execute("CREATE TABLE IF NOT EXISTS mac_addresses ("
                  "node_id INT AUTO_INCREMENT PRIMARY KEY, "
                  "mac_address VARCHAR(50) NOT NULL, "
                  "System_Name VARCHAR(50) NOT NULL)");
            delete stmt;

            // Create the 'client_Info' table with a foreign key reference to 'mac_addresses'
            stmt = dbConnection->createStatement();
            stmt->execute("CREATE TABLE IF NOT EXISTS client_Info ("
                          "id INT AUTO_INCREMENT PRIMARY KEY, "
                          "node_id INT, "
                          "timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
                          "RAM_Usage FLOAT, "
                          "CPU_Utilization FLOAT, "
                          "Idle_Time FLOAT, "
                          "HDD_Utilization FLOAT, "
                          "Network_Stats VARCHAR(50), "
                          "FOREIGN KEY (node_id) REFERENCES mac_addresses(node_id))");
            delete stmt;

            std::cout << "Tables created successfully." << std::endl;
 }
  catch (sql::SQLException &e) {
            std::cerr << "MySQL Error: " << e.what() << std::endl;
            
        }
  }
  
 };
 
 class CSVWriter {
public:
    CSVWriter(const std::string& filename) : filename_(filename) {
        openFile();
    }

    ~CSVWriter() {
        if (csvFile_.is_open()) {
            csvFile_.close();
        }
    }

    void writeData(const std::vector<std::string>& data) {
        if (!csvFile_.is_open()) {
            std::cerr << "Error opening CSV file for writing." << std::endl;
            return;
        }

        if (isEmpty()) {
            addColumnNames();
        }

        for (const std::string& field : data) {
            csvFile_ << field << ",";
        }
        csvFile_ << std::endl;
    }

private:
    std::string filename_;
    std::ofstream csvFile_;

    void openFile() {
        csvFile_.open(filename_, std::ios::out | std::ios::app);
    }

    bool isEmpty() {
        csvFile_.seekp(0, std::ios::end);
        return csvFile_.tellp() == 0;
    }

    void addColumnNames() {
        std::vector<std::string> c_name = {
            "MAC address", "System Name", "Date", "Time",
            "RAM Usage", "CPU Utilization", "Idle Time",
            "HDD utilization", "Network stats"
        };

        for (const std::string& field : c_name) {
            csvFile_ << field << ",";
        }
        csvFile_ << std::endl;
    }
};

class DatabaseHandler {
public:
    DatabaseHandler(sql::Connection *dbConnection) : dbConnection(dbConnection) {
        if (!dbConnection) {
            throw std::runtime_error("Database connection is not valid.");
        }
    }
     // Function to insert a new MAC address into the 'mac_addresses' table
    void insertMacAddress(const string &macAddr, const string &sys_n) {
        sql::PreparedStatement *pstmt;
        pstmt = dbConnection->prepareStatement("INSERT INTO mac_addresses (mac_address, System_Name) VALUES (?, ?)");
        pstmt->setString(1, macAddr);
        pstmt->setString(2, sys_n);
        int result = pstmt->executeUpdate();
        delete pstmt;
        
    }
    // Function to get the node_id for a MAC address
    int getNodeID(const string &macAddr) {
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

    int insertClientData(int node_id, const string &ram, const string &cpu, const string &idle, const string &hdd, const string &netw) {
        sql::PreparedStatement *pstmt;
        pstmt = dbConnection->prepareStatement("INSERT INTO client_Info (node_id, RAM_Usage, CPU_Utilization, Idle_Time, HDD_Utilization, Network_Stats) VALUES (?, ?, ?, ?, ?, ?)");
        pstmt->setInt(1, node_id);
        pstmt->setString(2, ram);
        pstmt->setString(3, cpu);
        pstmt->setString(4, idle);
        pstmt->setString(5, hdd);
        pstmt->setString(6, netw);
        pstmt->execute();
        delete pstmt;
        return 0; // You can return an appropriate status code or handle errors as needed
    }

private:
    sql::Connection *dbConnection;
};



// Function to handle a single client commuication 
void handleClient(tcp::socket clientSocket, sql::Connection *dbConnection) {
boost::asio::ip::tcp::endpoint remoteEndpoint = clientSocket.remote_endpoint();

    std::string clientAddress = remoteEndpoint.address().to_string();

 

    // Check if the client's IP address is whitelisted

    if (!isWhitelisted(clientAddress)) {

        std::cout << "Connection from non-whitelisted IP: " << clientAddress << " denied." << std::endl;

        return;

    }

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
    } catch (exception &e) {
        cerr << "Error: " << e.what() << endl;
        boost::asio::write(clientSocket, boost::asio::buffer("Error in sending info\0", 24));
    }
}

 

int main() {
    boost::asio::io_context ioContext;  //central part of Boost.Asio that provides I/O services and event handling for asynchronous operations.
    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 12345));
    vector<thread> clientThreads;

    DatabaseConnector dbConnector("tcp://localhost:3306", "Project", "Project@123456789");
    

    if (!dbConnector.connectToDatabase()) {
        cout<<"Database Connection failure "<<endl;
        return 0;
    } 
     std::cout << "Connected to the database." << std::endl;
     
        DbStructure &Dbstructure=DbStructure::getInstance(dbConnector.dbConnection);
        Dbstructure.CreateDb();
        Dbstructure.CreateTables();
       
    while (true) {
    //clientSocket(declared TCP socket) socket will be used to communicate with an individual client, ioContext allow asynchronous I/O operations 
        tcp::socket clientSocket(ioContext); 
        cout << "Server is listening on port 12345..." << endl;
        acceptor.accept(clientSocket);//accept client connection and give that to clientsocket 
        
        // Create a new thread to handle the client connection
        //new thread for each client,each new thread execute the handleclient funtion to handle the client's communication.
        clientThreads.emplace_back(handleClient, move(clientSocket), dbConnector.dbConnection);
    }

 

    // Wait for all client threads to finish
    for (thread &t : clientThreads) {
        t.join();
    }

 

    // Close the database connection when done
    dbConnector.disconnectFromDatabase();

 

    return 0;
}
