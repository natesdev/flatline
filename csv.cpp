#include <stdio.h>
#include "csv.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

int CSV::splitText(std::vector<std::string> &ptr, std::string text, char delimiter)
{
    std::vector<std::string> words;
    std::string word = "";
    bool inQuotes = false;
    if (text[0] == '"')
    {
        inQuotes = true;
    }

    for (char c : text)
    {
        if (c == '"')
        {
            inQuotes = !inQuotes;
        }
        else if (c == delimiter && !inQuotes)
        {
            words.push_back(word);
            word = "";
        }
        else
        {
            word += c;
        }
    }
    words.push_back(word);
    ptr = words;
    return 0;
}

std::vector<std::string> CSV::getColumns(std::string CSVPath)
{
    std::fstream file;
    std::string str;
    std::vector<std::string> splitString;

    file.open(CSVPath, std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open())
    {
        std::ofstream newFile(CSVPath);
        newFile.close();
        file.open(CSVPath, std::ios::in | std::ios::out | std::ios::app);
    }
    if (std::getline(file, str) && !str.empty())
    {
        splitText(splitString, str, ',');
    }

    return splitString;
}

std::vector<Row> CSV::getRows(std::string CSVPath)
{
    std::fstream file(CSVPath);
    std::string line;
    std::vector<Row> rows;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::vector<std::string> rowData;
        splitText(rowData, line, ',');
        rows.push_back(Row(this, rowData));
    }

    return rows;
}

int CSV::readCSV(std::string CSVPath)
{
    rows = getRows(CSVPath);
    columns = getColumns(CSVPath);
    path = CSVPath;
    return 0;
}

int CSV::writeCSV()
{
    std::ofstream file(path);

    for (size_t i = 0; i < columns.size(); ++i)
    {
        if (!columns[i].empty())
        {
            file << columns[i];
        }
        if (i < columns.size() - 1)
        {
            file << ",";
        }
    }

    file << std::endl;

    for (const auto &row : rows)
    {
        for (size_t i = 0; i < row.row.size(); ++i)
        {
            file << row.row[i];
            if (i < row.row.size() - 1)
            {
                file << ",";
            }
        }
        file << std::endl;
    }
    file.close();

    return 0;
}

int CSV::addRow(const std::vector<std::string> &rowData)
{
    if (rowData.size() != columns.size())
    {
        throw std::invalid_argument("Row size does not match the number of columns");
    }
    rows.push_back(Row(this, rowData));
    return rows.size() - 1;
}

void CSV::addColumn(const std::string &columnName)
{
    columns.push_back(columnName);
    for (auto &row : rows)
    {
        row.row.push_back("");
    }
}

int CSV::getRowIndex(const std::string &rowName)
{
    for (size_t i = 0; i < rows.size(); ++i)
    {
        if (!rows[i].row.empty() && rows[i].row[0] == rowName)
        {
            return i;
        }
    }
    return -1;
}

int CSV::getColumnIndex(const std::string &columnName)
{
    for (size_t i = 0; i < columns.size(); ++i)
    {
        if (columns[i] == columnName)
        {
            return i;
        }
    }
    return -1;
}

CSV::CSV(std::string CSVPath)
{
    if (!std::filesystem::exists(CSVPath))
    {
        std::ofstream newFile(CSVPath);
        newFile.close();
    }
    readCSV(CSVPath);
}

std::string &Row::operator[](const std::string &columnName)
{
    int index = csv->getColumnIndex(columnName);
    if (index == -1)
    {
        throw std::out_of_range("Column not found");
    }
    return row[index];
}

std::string &Row::operator[](const int &index)
{
    return row[index];
}

Row &Row::operator=(const Row &other)
{
    if (this == &other)
    {
        return *this;
    }

    row = other.row;
    csv = other.csv;
    return *this;
}
