#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <string>
#include <mysql_driver.h>
#include <cppconn/connection.h>

class DatabaseConnector {
public:
    sql::Connection *dbConnection;
    DatabaseConnector(const std::string &server_, const std::string &username_, const std::string &password_);
    bool connectToDatabase();
    void disconnectFromDatabase();

private:
    sql::mysql::MySQL_Driver *driver;
    std::string server;
    std::string username;
    std::string password;
};

#endif // DATABASE_CONNECTOR_H

