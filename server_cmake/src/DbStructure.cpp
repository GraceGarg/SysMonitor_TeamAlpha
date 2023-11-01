
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>  // Include the statement header

#include "DbStructure.h"


DbStructure::DbStructure(sql::Connection *dbConnection) : dbConnection(dbConnection) {
    if (!dbConnection) {
        throw std::runtime_error("Database connection is not valid.");
    }
}

DbStructure &DbStructure::getInstance(sql::Connection *dbConnection) {
    static DbStructure instance(dbConnection);
    return instance;
}

void DbStructure::CreateDb() {
    try {
        sql::Statement *createDbStmt = dbConnection->createStatement();
        createDbStmt->execute("CREATE DATABASE IF NOT EXISTS SystemInfo");
        delete createDbStmt;

        dbConnection->setSchema("SystemInfo");
    } catch (sql::SQLException &e) {
        std::cerr << "MySQL Error: " << e.what() << std::endl;
    }
}

void DbStructure::CreateTables() {
    try {
        sql::Statement *stmt = dbConnection->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS mac_addresses ("
                      "node_id INT AUTO_INCREMENT PRIMARY KEY, "
                      "mac_address VARCHAR(50) NOT NULL, "
                      "System_Name VARCHAR(50) NOT NULL)");
        delete stmt;

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
    } catch (sql::SQLException &e) {
        std::cerr << "MySQL Error: " << e.what() << std::endl;
    }
}

