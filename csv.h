#ifndef CSV_H
#define CSV_H

#include <vector>
#include <string>
#include <map>
#include "mod.h"

class CSVHandler
{
public:
    std::vector<std::string> getColumns(std::string CSVPath);
    std::vector<std::vector<std::string>> getRows(std::string CSVPath);
    int mergeCSVs();
    int setInputFiles(std::vector<std::string> inputFiles)
    {
        this->inputFiles = inputFiles;
        return 0;
    }
    int setOutputFolder(std::string outputFolder)
    {
        this->outputFolder = outputFolder;
        return 0;
    }
    int setCSVPaths(std::vector<std::pair<std::string, std::vector<std::string>>> CSVPaths)
    {
        this->CSVPaths = CSVPaths;
        return 0;
    }
    int getColumnIndex(std::string CSVPath, std::string columnName);

private:
    int splitText(std::vector<std::string> &ptr, std::string text, char delimiter);
    std::vector<std::string> inputFiles;
    std::string outputFolder;
    std::vector<std::pair<std::string, std::vector<std::string>>> CSVPaths;
};

#endif
