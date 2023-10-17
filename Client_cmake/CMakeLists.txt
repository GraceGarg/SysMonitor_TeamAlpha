cmake_minimum_required(VERSION 3.5)
project(client_cmake)

set(CMAKE_CXX_STANDARD 11)

add_executable(client_cmake
    src/main.cpp
    src/socketHandler.cpp
    src/dataHandler.cpp
    src/Logger.cpp)

target_include_directories(client_cmake PRIVATE src)
