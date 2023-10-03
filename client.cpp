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

using namespace std;

 

// Function to read and parse RAM usage from /proc/meminfo
string getRamUsage() {
    ifstream memInfoFile("/proc/meminfo");
    if (!memInfoFile.is_open()) {
        return "Failed to read RAM usage";
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
    return "RAM Usage: " + to_string(ramUsage) + "%";
}

 // Function to get system hostname 
string getSystemName() { 
    char hostname[1024]; 
    if (gethostname(hostname, sizeof(hostname)) == -1) { 
        return "Failed to get system name"; 
    } 

    return "System Name: " + string(hostname); 
} 

// Function to read and parse HDD utilization from /proc/mounts
string getHddUtilization() {
    ifstream mountsFile("/proc/mounts");
    if (!mountsFile.is_open()) {
        return "Failed to read HDD utilization";
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
    return "HDD Utilization: " + to_string(hddUtilization) + "%";
}


string getIdleTime() {
    ifstream uptimeFile("/proc/uptime");
    if (!uptimeFile.is_open()) {
        return "Failed to read idle time";
    }

    double uptime, idleTime;
    uptimeFile >> uptime >> idleTime;

    return "Idle Time: " + to_string(idleTime) + " seconds";
}
 

// Function to check network connectivity
bool isNetworkConnected() {
    string command = "ping -c 1 10.11.244.212"; // Replace with a known server or IP address
    int exitCode = system(command.c_str());
    return (exitCode == 0); // 0 indicates successful ping
}

 

// Function to read and parse CPU utilization from /proc/stat
string getCpuUtilization() {
    ifstream statFile("/proc/stat");
    if (!statFile.is_open()) {
        return "Failed to read CPU utilization";
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
    return "CPU Utilization: " + to_string(utilization) + "%";
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
    serverAddr.sin_addr.s_addr = inet_addr("10.11.244.212"); // Replace with the server's IP address

 

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error in connect");
        exit(EXIT_FAILURE);
    }

 

    // Create a loop to continuously send updates to the server
    while (true) {
        // Get RAM usage, HDD utilization, network status, CPU utilization, and idle time
        string ramUsage = getRamUsage();
        string hddUtilization = getHddUtilization();
        string networkStatus = isNetworkConnected() ? "Connected" : "Not Connected";
        string cpuUtilization = getCpuUtilization();
        string idleTime = getIdleTime();

 

        // Concatenate the data into a single string
        string clientData = "\n" +
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
