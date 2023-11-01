#include "DatabaseConnector.h"

DatabaseConnector::DatabaseConnector(const std::string &server_, const std::string &username_, const std::string &password_)
    : server(server_), username(username_), password(password_) {
    driver = sql::mysql::get_mysql_driver_instance();
}

bool DatabaseConnector::connectToDatabase() {
    try {
        dbConnection = driver->connect(server, username, password);
        return true;
    } catch (sql::SQLException &e) {
        return false;
    }
}

void DatabaseConnector::disconnectFromDatabase() {
    if (dbConnection) {
        dbConnection->close();
        delete dbConnection;
    }
}

