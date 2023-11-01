#include "CSVWriter.h"
#include <iostream>
CSVWriter::CSVWriter(const std::string &filename) : filename_(filename) {
    openFile();
}

CSVWriter::~CSVWriter() {
    if (csvFile_.is_open()) {
        csvFile_.close();
    }
}

void CSVWriter::writeData(const std::vector<std::string> &data) {
    if (!csvFile_.is_open()) {
        std::cerr << "Error opening CSV file for writing." << std::endl;
        return;
    }

    if (isEmpty()) {
        addColumnNames();
    }

    for (const std::string &field : data) {
        csvFile_ << field << ",";
    }
    csvFile_ << std::endl;
}

void CSVWriter::openFile() {
    csvFile_.open(filename_, std::ios::out | std::ios::app);
}

bool CSVWriter::isEmpty() {
    csvFile_.seekp(0, std::ios::end);
    return csvFile_.tellp() == 0;
}

void CSVWriter::addColumnNames() {
    std::vector<std::string> c_name = {
        "MAC address", "System Name", "Date", "Time",
        "RAM Usage", "CPU Utilization", "Idle Time",
        "HDD utilization", "Network stats"
    };

    for (const std::string &field : c_name) {
        csvFile_ << field << ",";
    }
    csvFile_ << std::endl;
}

