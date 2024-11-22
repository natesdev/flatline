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
    int mergeCSVs(std::string inputFolder, std::string outputFolder, std::vector<std::pair<std::string, std::vector<std::string>>> CSVPaths);
    int getColumnIndex(std::vector<std::string> columns, std::string columnName);

private:
    int splitText(std::vector<std::string> &ptr, std::string text, char delimiter);
};

#endif
