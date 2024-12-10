#include <stdio.h>
#include "csv.h"
#include "mod.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

/* Splits a string by a delimiter and returns a vector of strings */
int CSVHandler::splitText(std::vector<std::string> &ptr, std::string text, char delimiter)
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
        if (c == '"' and inQuotes)
        {
        }
        else if (c == delimiter)
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

/* Returns all columns inside of a CSV file */
std::vector<std::string> CSVHandler::getColumns(std::string CSVPath)
{
    std::fstream file;
    std::string str;
    std::vector<std::string> splitString;

    file.open(CSVPath, std::ios::in);
    std::getline(file, str);
    splitText(splitString, str, ',');

    return splitString;
}

/* Returns all rows inside of CSV file */
std::vector<std::vector<std::string>> CSVHandler::getRows(std::string CSVPath)
{
    std::fstream file(CSVPath);
    std::string line;
    std::vector<std::vector<std::string>> rows;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::vector<std::string> rowData;
        splitText(rowData, line, ',');
        rows.push_back(rowData);
    }

    return rows;
}

CSV CSVHandler::readCSV(std::string CSVPath)
{
    auto rows = getRows(CSVPath);
    auto columns = getColumns(CSVPath);
    CSV csv;
    csv.columns = columns;
    for (const auto &rowData : rows)
    {
        csv.rows.push_back(Row(&csv, rowData)); // Pass pointer to the CSV instance
    }
    return csv;
}

/* Merges multiple CSVs together */
int CSVHandler::mergeCSVs(std::string inputFolder, std::string outputFolder, std::vector<std::pair<std::string, std::vector<std::string>>> CSVPaths)
{
    for (const auto &[CSVFolder, CSVFiles] : CSVPaths)
    {
        for (const std::string &CSVFile : CSVFiles)
        {
            std::string input = inputFolder + "/" + CSVFolder + "/" + CSVFile;
            std::string output = outputFolder + "/" + CSVFolder + "/" + CSVFile;
            std::vector<std::vector<std::string>> inputRows = getRows(input);
            std::vector<std::vector<std::string>> outputRows = getRows(output);

            for (const std::vector<std::string> &inputRow : inputRows)
            {
                bool found = false;
                std::string identifier = inputRow[0];
                for (const std::vector<std::string> &outputRow : outputRows)
                {
                    if (outputRow[0] == identifier)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    outputRows.push_back(inputRow);
                }
            }
        }
    }

    return 0;
}

int CSV::writeCSV()
{
    std::ofstream file(path);
    for (size_t i = 0; i < columns.size(); ++i)
    {
        file << columns[i];
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

std::string Row::operator[](const std::string &columnName)
{
    int index = csv->getColumnIndex(columnName);
    if (index == -1)
    {
        throw std::out_of_range("Column not found");
    }
    return row[index];
}

std::string Row::operator[](const int &columnIndex)
{
    return row[columnIndex];
}

Row &Row::operator=(const Row &other)
{
    if (this == &other)
    {
        return *this;
    }

    row = other.row;
    return *this;
}