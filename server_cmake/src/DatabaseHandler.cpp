#include "DatabaseHandler.h"
DatabaseHandler::DatabaseHandler(sql::Connection *dbConnection) : dbConnection(dbConnection) {
    if (!dbConnection) {
        throw std::runtime_error("Database connection is not valid.");
    }
}

void DatabaseHandler::insertMacAddress(const std::string &macAddr, const std::string &sys_n) {
    sql::PreparedStatement *pstmt;
    pstmt = dbConnection->prepareStatement("INSERT INTO mac_addresses (mac_address, System_Name) VALUES (?, ?)");
    pstmt->setString(1, macAddr);
    pstmt->setString(2, sys_n);
    int result = pstmt->executeUpdate();
    delete pstmt;
}

int DatabaseHandler::getNodeID(const std::string &macAddr) {
    sql::Statement *stmt = dbConnection->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT node_id FROM mac_addresses WHERE mac_address = '" + macAddr + "'");
    int node_id = -1;
    if (res->next()) {
        node_id = res->getInt("node_id");
    }
    delete res;
    delete stmt;
    return node_id;
}

int DatabaseHandler::insertClientData(int node_id, const std::string &ram, const std::string &cpu, const std::string &idle, const std::string &hdd, const std::string &netw) {
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

