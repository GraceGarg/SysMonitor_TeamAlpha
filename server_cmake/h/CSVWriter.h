#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <string>
#include <vector>
#include <fstream>
class CSVWriter {
public:
    CSVWriter(const std::string &filename);
    ~CSVWriter();
    void writeData(const std::vector<std::string> &data);

private:
    std::string filename_;
    std::ofstream csvFile_;
    void openFile();
    bool isEmpty();
    void addColumnNames();
};

#endif // CSV_WRITER_H

