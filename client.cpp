#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <ctime>
#include<vector>
#include <iomanip>
#include <sstream>
#include<ctime>

using namespace std;

class socketHandler{ 

    public: 
    string serverAddress; 
    int serverPort; 

     static socketHandler& getInstance() 
     { 
     static socketHandler Instance; 
      cout<<"Enter Server Address"<<endl; 

        cin>>Instance.serverAddress; 
        cout<<"Enter Server Port"<<endl; 
        cin>>Instance.serverPort; 
     return Instance; 
     } 

    int connectToServer() 
    { 
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

    private: 
    socketHandler() { 
        // Constructor code here 
    } 

    // Private copy constructor and assignment operator to prevent copying 
    socketHandler(const socketHandler&) = delete; 
    socketHandler& operator=(const socketHandler&) = delete; 

};

class dataHandler{
    private:
        string systemId;
        string systemName;
        string networkStatus;
        string ramUsage;
        string hddUtilization;
        string idleTime;
        string cpuUtilization;

    //get mac address
    string getMacAddress() {
    // Run the ifconfig or ip command to get network interface information
    FILE* pipe = popen("ifconfig", "r"); // You can use "ip link" for newer systems
    if (!pipe) {
        perror("Error opening pipe");
        return "Failed_to_get_MAC_address";
    }

    char buffer[128];
    std::string result = "";

    // Read the output of the command line by line
    while (!feof(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
    } 

    pclose(pipe);

    // Find and extract the MAC address from the result (for "ether" lines)
    size_t macPos = result.find("ether");
    if (macPos != std::string::npos) {
        size_t start = macPos + 6; // Position after "ether"
        size_t end = start + 17;  // MAC address length (17 characters)
        return result.substr(start, end - start);
    }

    return "MAC_address_not_found";
}

    // Function to get system hostname 
    string getSystemName() { 
        char hostname[1024]; 
        if (gethostname(hostname, sizeof(hostname)) == -1) { 
            return "Failed_to_get_system_name"; 
        } 

        return string(hostname); 
    } 

    // Function to read and parse RAM usage from /proc/meminfo
    string getRamUsage() {
        ifstream memInfoFile("/proc/meminfo");
        if (!memInfoFile.is_open()) {
            return "Failed_to_read_RAM_usage";
        }

        string line;
        long totalMem = 0, freeMem = 0;
        while (getline(memInfoFile, line)) {
            istringstream ss(line);
            string field;
            long value;
            ss >> field >> value;

            if (field == "MemTotal:") {
                totalMem = value;
            } else if (field == "MemFree:") {
                freeMem = value;
            }
        }

        long usedMem = totalMem - freeMem;
        double ramUsage = static_cast<double>(usedMem) / totalMem * 100.0;

        return to_string(ramUsage);
    }

    // Function to check network connectivity
    bool isNetworkConnected() {
        string command = "ping -c 1 " + serverAddress; // Replace with a known server or IP address
        int exitCode = system(command.c_str());
        return (exitCode == 0); // 0 indicates successful ping
    }

    // Function to read and parse HDD utilization from /proc/mounts
    string getHddUtilization() {
        ifstream mountsFile("/proc/mounts");
        if (!mountsFile.is_open()) {
            return "Failed_to_read_HDD_utilization";
        }

        vector<string> mountedDevices;
        string line;
        while (getline(mountsFile, line)) {
            istringstream ss(line);
            string device, mountPoint;
            ss >> device >> mountPoint;
            if (!device.empty() && device != "none" && device != "rootfs") {
                mountedDevices.push_back(mountPoint);
            }
        }

        long totalHdd = 0, freeHdd = 0;
        for (const string &device : mountedDevices) {
            string command = "df -h " + device + " | awk 'NR==2 {print $5}'";
            FILE *pipe = popen(command.c_str(), "r");
            if (pipe) {
                char buffer[32];
                if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                    long hddUsage;
                    if (sscanf(buffer, "%ld%%", &hddUsage) == 1) {
                        totalHdd += 100; // Assume 100% total for all devices
                        freeHdd += 100 - hddUsage;
                    }
                }
                pclose(pipe);
            }
        }

        if (totalHdd == 0) {
            return "HDD Utilization: N/A";
        } 

        double hddUtilization = static_cast<double>(freeHdd) / totalHdd * 100.0;
        return to_string(hddUtilization);
    }

    //get Idle time
    string getIdleTime() {
        ifstream uptimeFile("/proc/uptime");
        if (!uptimeFile.is_open()) {
            return "Failed_to_read_idle_time";
        }

        double uptime, idleTime;
        uptimeFile >> uptime >> idleTime;

        return to_string(idleTime);
    }

    // Function to read and parse CPU utilization from /proc/stat
    string getCpuUtilization() {
        ifstream statFile("/proc/stat");
        if (!statFile.is_open()) {
            return "Failed_to_read_CPU_utilization";
        }

        string line;
        getline(statFile, line);
        istringstream ss(line);
        string cpuLabel;
        long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
        ss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

        long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;
        long idleTime = idle;

        double utilization = 100.0 * (totalTime - idleTime) / totalTime;
        return to_string(utilization);
    }

    string getCurrentDateTimeAsString() {
    // Get the current time
    time_t currentTime = time(nullptr);

    // Create a buffer to store the formatted date and time
    char buffer[80]; // Adjust the buffer size as needed

    // Format the current time as a string
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

    // Convert the buffer to a C++ string
    string dateTimeString(buffer);
    cout<<dateTimeString<<endl;
    return dateTimeString;
}


    public:
    string serverAddress;
    dataHandler(string ipAddress){
        serverAddress = ipAddress;
    }
    string clientData;
    //fethcing sysInfo and concatenate it
    string fetchData(){

        systemName = getSystemName();
        networkStatus = isNetworkConnected() ? "Connected" : "NotConnected";
        ramUsage = getRamUsage();
        hddUtilization = getHddUtilization();
        idleTime = getIdleTime();
        cpuUtilization = getCpuUtilization();

 

        // Concatenate the data into a single string
        clientData =    getMacAddress() + " "+ "\n" + 
                        systemName + " " + "\n" +
                        getCurrentDateTimeAsString() + " "+ "\n" +
                        ramUsage + " " + "\n" +
                        cpuUtilization + " "+ "\n" +
                        idleTime + " "+ "\n" +
                        hddUtilization + " "+ "\n" +
                        networkStatus;
                       
        return clientData;
    }
    
};

int main() {
    // Create a socket for the client
    socketHandler &obj1 = socketHandler::getInstance();
    string serverIpAddress=obj1.serverAddress;
    int clientSocket = obj1.connectToServer();

    dataHandler obj2(serverIpAddress);
    // Create a loop to continuously send updates to the server
    while (true) {
        string clientData = obj2.fetchData();

        // Send the client data to the server
        send(clientSocket, clientData.c_str(), clientData.length(), 0);

        // Sleep for 5 seconds before sending the next update
        sleep(5);
    }

    close(clientSocket);
    return 0;
}
