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

 

// Function to read and parse RAM usage from /proc/meminfo
std::string getRamUsage() {
    std::ifstream memInfoFile("/proc/meminfo");
    if (!memInfoFile.is_open()) {
        return "Failed to read RAM usage";
    }

 

    std::string line;
    long totalMem = 0, freeMem = 0;
    while (std::getline(memInfoFile, line)) {
        std::istringstream ss(line);
        std::string field;
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
    return "RAM Usage: " + std::to_string(ramUsage) + "%";
}

 // Function to get system hostname 
std::string getSystemName() { 
    char hostname[1024]; 
    if (gethostname(hostname, sizeof(hostname)) == -1) { 
        return "Failed to get system name"; 
    } 

    return "System Name: " + std::string(hostname); 
} 

// Function to read and parse HDD utilization from /proc/mounts
std::string getHddUtilization() {
    std::ifstream mountsFile("/proc/mounts");
    if (!mountsFile.is_open()) {
        return "Failed to read HDD utilization";
    }

 

    std:: vector<std::string> mountedDevices;
    std::string line;
    while (std::getline(mountsFile, line)) {
        std::istringstream ss(line);
        std::string device, mountPoint;
        ss >> device >> mountPoint;
        if (!device.empty() && device != "none" && device != "rootfs") {
            mountedDevices.push_back(mountPoint);
        }
    }

 

    long totalHdd = 0, freeHdd = 0;
    for (const std::string &device : mountedDevices) {
        std::string command = "df -h " + device + " | awk 'NR==2 {print $5}'";
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
    return "HDD Utilization: " + std::to_string(hddUtilization) + "%";
}


std::string getIdleTime() {
    std::ifstream uptimeFile("/proc/uptime");
    if (!uptimeFile.is_open()) {
        return "Failed to read idle time";
    }

    double uptime, idleTime;
    uptimeFile >> uptime >> idleTime;

    return "Idle Time: " + std::to_string(idleTime) + " seconds";
}
 

// Function to check network connectivity
bool isNetworkConnected() {
    std::string command = "ping -c 1 10.11.244.200"; // Replace with a known server or IP address
    int exitCode = system(command.c_str());
    return (exitCode == 0); // 0 indicates successful ping
}

 

// Function to read and parse CPU utilization from /proc/stat
std::string getCpuUtilization() {
    std::ifstream statFile("/proc/stat");
    if (!statFile.is_open()) {
        return "Failed to read CPU utilization";
    }

 

    std::string line;
    std::getline(statFile, line);
    std::istringstream ss(line);
    std::string cpuLabel;
    long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    ss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

 

    long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;
    long idleTime = idle;

 

    double utilization = 100.0 * (totalTime - idleTime) / totalTime;
    return "CPU Utilization: " + std::to_string(utilization) + "%";
}

 

int main() {
    // Create a socket for the client
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }

 

    // Define the server address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Replace with the server's port
    serverAddr.sin_addr.s_addr = inet_addr("10.11.244.200"); // Replace with the server's IP address

 

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error in connect");
        exit(EXIT_FAILURE);
    }

 

    // Create a loop to continuously send updates to the server
    while (true) {
        // Get RAM usage, HDD utilization, network status, CPU utilization, and idle time
        std::string ramUsage = getRamUsage();
        std::string hddUtilization = getHddUtilization();
        std::string networkStatus = isNetworkConnected() ? "Connected" : "Not Connected";
        std::string cpuUtilization = getCpuUtilization();
        std::string idleTime = getIdleTime();

 

        // Concatenate the data into a single string
        std::string clientData = "Client Data:\n" +
        			 getSystemName() + "\n" +
                                 ramUsage + "\n" +
                                 hddUtilization + "\n" +
                                 networkStatus + "\n" +
                                 cpuUtilization + "\n" +
                                 idleTime;

 

        // Send the client data to the server
        send(clientSocket, clientData.c_str(), clientData.length(), 0);

 

        // Sleep for 5 seconds before sending the next update
        sleep(5);
    }

 

    close(clientSocket);
    return 0;
}
