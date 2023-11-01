#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <stdexcept>
#include <mysql_driver.h>


class DatabaseHandler {
public:
    DatabaseHandler(sql::Connection *dbConnection);
    void insertMacAddress(const std::string &macAddr, const std::string &sys_n);
    int getNodeID(const std::string &macAddr);
    int insertClientData(int node_id, const std::string &ram, const std::string &cpu, const std::string &idle, const std::string &hdd, const std::string &netw);

private:
    sql::Connection *dbConnection;
};

#endif // DATABASE_HANDLER_H

