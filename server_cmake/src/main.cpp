#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include "DatabaseConnector.h"
#include "DbStructure.h"
#include "handleclient.h"

using namespace std;
using namespace boost::asio;
using ip::tcp;

int main() {
    boost::asio::io_context ioContext;
    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 12345));
    vector<thread> clientThreads;

    DatabaseConnector dbConnector("tcp://localhost:3306", "Project", "Project@123456789");

    if (!dbConnector.connectToDatabase()) {
        cout << "Database Connection failure " << endl;
        return 0;
    }
    cout << "Connected to the database." << endl;

    DbStructure &dbStructure = DbStructure::getInstance(dbConnector.dbConnection);
    dbStructure.CreateDb();
    dbStructure.CreateTables();

    while (true) {
        tcp::socket clientSocket(ioContext);
        cout << "Server is listening on port 12345..." << endl;
        acceptor.accept(clientSocket);

        clientThreads.emplace_back(handleClient, move(clientSocket), dbConnector.dbConnection);
    }

    for (thread &t : clientThreads) {
        t.join();
    }

    dbConnector.disconnectFromDatabase();

    return 0;
}

