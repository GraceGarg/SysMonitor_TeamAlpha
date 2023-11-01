#pragma once
#include <boost/asio.hpp>
#include <cppconn/connection.h>

void handleClient(boost::asio::ip::tcp::socket clientSocket, sql::Connection *dbConnection);

