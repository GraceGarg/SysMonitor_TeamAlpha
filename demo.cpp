#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <fstream>
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
using namespace std;

using namespace boost::asio;
using ip::tcp;

   
// Define the data structure to hold SystemConfig data
struct SystemConfigData {
    string MacAddress;
    string systemName;
    string Date;
    string Time;
    string ramUsage;
    string cpuUtilization;
    string idleTime;
    string hddUtilization;
    string networkStats;
    
    
    SystemConfigData(const string& mac, const string& name, const string& date, const string& time, const string& ram, const string& cpu, const string& idle, const string& hdd, const string& stats )
        : MacAddress(mac), systemName(name), Date(date), Time(time), ramUsage(ram), cpuUtilization(cpu), idleTime(idle), hddUtilization(hdd), networkStats(stats) {}
};  


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

           // cout << endl << "Received Data from Client: " << buffer << endl;
            
            
            stringstream ss(buffer);
            vector<string> vec1;
            string str1;
            while(ss>>str1)
            {
            vec1.push_back(str1);
            }
            string macAddr=vec1[0];
            string sys_n=vec1[1];
            string date=vec1[2];
            string time=vec1[3];
            string ram=vec1[4];
            string cpu=vec1[5];
            string idle=vec1[6];
            string hdd=vec1[7];
             string  netw=vec1[8];
            
            
           
            cout<<macAddr<<endl<<sys_n<<endl<<date<<endl<<time<<endl<<ram<<endl<<cpu<<endl<<idle<<endl<<hdd<<endl<<netw;
            
            
            // Create a SystemConfigData object with fetched data (replace with your fetching logic)
           SystemConfigData configData(macAddr, sys_n, date, time, ram, cpu, idle, hdd, netw);

	
		
            // Insert the received data into the MySQL database
            sql::PreparedStatement *pstmt;
            pstmt = dbConnection->prepareStatement("INSERT INTO SystemData (Mac_Address,System_Name, Recieved_Date, Recieved_Time, RAM_Usage, CPU_Utilization, Idle_Time, HDD_Utilization, Network_Stats) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
            
            // Set values for each placeholder using the fetched data
                pstmt->setString(1, configData.MacAddress);
                pstmt->setString(2, configData.systemName);
                pstmt->setString(3, configData.Date);
                pstmt->setString(4, configData.Time);
		pstmt->setString(5, configData.ramUsage);
		pstmt->setString(6, configData.cpuUtilization);
		pstmt->setString(7, configData.idleTime);
		pstmt->setString(8, configData.hddUtilization);
		pstmt->setString(9, configData.networkStats);
		
	
            
            pstmt->execute();
            delete pstmt;
        }
    } catch (exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    boost::asio::io_context ioContext;

    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 12345)); 
    vector<thread> clientThreads; // Store client threads

    // Initialize MySQL Connector/C++
    sql::mysql::MySQL_Driver *driver;
    driver = sql::mysql::get_mysql_driver_instance();
    sql::Connection *dbConnection;
    dbConnection = driver->connect("tcp://localhost:3306", "Project", "Project@123456789");
    
    cout<< "Database is connected";
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

