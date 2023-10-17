#include "dataHandler.h"
#include "main.h"
using namespace std;
dataHandler::dataHandler(const std::string& ipAddress) {
    serverAddress = ipAddress;
}

std::string dataHandler::fetchData() {
     systemName = getSystemName();
        networkStatus = isNetworkConnected(this->serverAddress) ? "Connected" : "NotConnected";
        ramUsage = getRamUsage();
        hddUtilization = getHddUtilization();
        idleTime = getIdleTime();
        cpuUtilization = getCpuUtilization();

 

        // Concatenate the data into a single string
        clientData =    getMacAddress() + " "+  
                        systemName + " " +
                        getCurrentDateTimeAsString() + " "+
                        ramUsage + " " +
                        cpuUtilization + " "+
                        idleTime + " "+
                        hddUtilization + " "+
                        networkStatus;
                       
        return clientData;
}
    
    string dataHandler::getMacAddress() {
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
    string dataHandler::getSystemName() { 
        char hostname[1024]; 
        if (gethostname(hostname, sizeof(hostname)) == -1) { 
            return "Failed_to_get_system_name"; 
        } 

        return string(hostname); 
    } 

    // Function to read and parse RAM usage from /proc/meminfo
    string dataHandler::getRamUsage() {
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
    bool dataHandler::isNetworkConnected(const std::string& ip ){
        string command = "ping -c 1 " + ip; // Replace with a known server or IP address
        int exitCode = system(command.c_str());
        return (exitCode == 0); // 0 indicates successful ping
    }

    // Function to read and parse HDD utilization from /proc/mounts
    string dataHandler::getHddUtilization() {
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
    string dataHandler::getIdleTime() {
        ifstream uptimeFile("/proc/uptime");
        if (!uptimeFile.is_open()) {
            return "Failed_to_read_idle_time";
        }

        double uptime, idleTime;
        uptimeFile >> uptime >> idleTime;

        return to_string(idleTime);
    }

    // Function to read and parse CPU utilization from /proc/stat
    string dataHandler::getCpuUtilization() {
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

    string dataHandler::getCurrentDateTimeAsString() {
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


