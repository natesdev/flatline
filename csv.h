#ifndef CSV_H
#define CSV_H

#include <vector>
#include <string>
#include <map>
#include <stdexcept>

class CSV;
class Row
{
public:
    std::vector<std::string> row;
    CSV *csv;

    Row(CSV *csv, std::vector<std::string> row) : csv(csv), row(row) {}

    std::string operator[](const std::string &columnName);
    std::string operator[](const int &columnIndex);

    Row &operator=(const Row &other);

    Row(std::initializer_list<std::string> initList) : row(initList) {}

    Row(std::vector<std::string> row) : row(row) {}
};

class CSV
{
public:
    std::vector<std::string> columns;
    std::vector<Row> rows;
    std::string path;

    int getColumnIndex(const std::string &columnName);
    int getRowIndex(const std::string &rowName);

    int writeCSV();
    CSV readCSV(std::string CSVPath);

private:
    int splitText(std::vector<std::string> &ptr, std::string text, char delimiter);
    std::vector<std::string> getColumns(std::string CSVPath);
    std::vector<Row> getRows(std::string CSVPath);
};

#endif
