#include <stdio.h>
#include "csv.h"
#include "mod.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int CSVHandler::splitText(std::vector<std::string> &ptr, std::string text, char delimiter)
{
    std::vector<std::string> words;
    std::string word = "";
    bool inQuotes = false;

    for (char c : text)
    {
        if (c == '"' && !inQuotes)
        {
            inQuotes = true;
        }
        else if (c == '"' && inQuotes)
        {
            inQuotes = false;
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

    if (!word.empty())
    {
        words.push_back(word);
    }

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

int CSVHandler::getColumnIndex(std::vector<std::string> columns, std::string columnName)
{
    for (int i = 0; i < columns.size(); i++)
    {
        if (columns[i] == columnName)
        {
            return i;
        }
    }
    return -1;
}

int CSVHandler::mergeCSVs()
{
    for (const auto &inputFile : inputFiles)
    {
        for (const auto &[CSVFolder, CSVFiles] : CSVPaths)
        {
            for (const std::string &CSVFile : CSVFiles)
            {
                std::string input = inputFile + "/" + CSVFolder + "/" + CSVFile;
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