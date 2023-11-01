cmake_minimum_required(VERSION 3.10)
project(server_cmake)

#set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.65 REQUIRED)
find_package(Threads REQUIRED)

# Provide a hint to CMake about the location of mysqlcppconn package config files

#set(CMAKE_PREFIX_PATH "/usr/share/cmake/mysqlcppconn")  # Replace with the actual path

include_directories(${CMAKE_SOURCE_DIR}/h)

add_executable(server_cmake
    src/main.cpp
    src/DatabaseConnector.cpp
    src/DbStructure.cpp
    src/handleclient.cpp
    src/CSVWriter.cpp
    src/DatabaseHandler.cpp
    
)

target_include_directories(server_cmake PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(server_cmake ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} mysqlcppconn)


