#include <stdio.h>
#include "csv.h"
#include "mod.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
        if (c == '"' and inQuotes) {}
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

/* Merges multiple CSVs together */
int CSVHandler::mergeCSVs(std::string inputFolder, std::string outputFolder, std::vector<std::pair<std::string, std::vector<std::string>>> CSVPaths)
{
    for (const auto &folder : inputFolder)
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
                        }
                    }
                    if (!found)
                    {
                        outputRows.push_back(inputRow);
                    }
                }
            }
        }
    }

    return 0;
}

CSV CSVHandler::readCSV(std::string CSVPath)
{
    auto rows = getRows(CSVPath);
    auto columns = getColumns(CSVPath);

    CSV csv;
    csv.columns = columns;
    csv.rows = rows;

    return csv;
}

int CSVHandler::writeCSV(std::string CSVPath, CSV csv)
{
    std::ofstream file(CSVPath);
    for (size_t i = 0; i < csv.columns.size(); ++i)
    {
        file << csv.columns[i];
        if (i < csv.columns.size() - 1)
        {
            file << ",";
        }
    }

    file << std::endl;

    for (const auto &row : csv.rows)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            file << row[i];
            if (i < row.size() - 1)
            {
                file << ",";
            }
        }
        file << std::endl;
    }

    file.close();

    return 0;
}

