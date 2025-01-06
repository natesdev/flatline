#ifndef FLATLINE_H
#define FLATLINE_H

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

    std::string &operator[](const int &columnIndex);
    std::string &operator[](const std::string &columnName);

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
    int writeCSV();
    int readCSV(std::string CSVPath);
    int addRow(const std::vector<std::string> &rowData);
    void addColumn(const std::string &columnName);
    int getColumnIndex(const std::string &columnName);
    int getRowIndex(const std::string &rowName);
    CSV(std::string CSVPath);
    CSV() {};

private:
    int splitText(std::vector<std::string> &ptr, std::string text, char delimiter);
    std::vector<std::string> getColumns(std::string CSVPath);
    std::vector<Row> getRows(std::string CSVPath);
};

#endif
