#ifndef CSV_H
#define CSV_H

#include <vector>
#include <string>
#include <map>
#include "mod.h"

struct CSV
{
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> rows;

    int getColumnIndex(const std::string &columnName)
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

    int getRowIndex(const std::string &rowName)
    {
        for (size_t i = 0; i < rows.size(); ++i)
        {
            if (!rows[i].empty() && rows[i][0] == rowName)
            {
                return i;
            }
        }
        return -1;
    }
};

class CSVHandler
{
public:
    // Deprecated use readCSV instead
    std::vector<std::string> getColumns(std::string CSVPath);
    std::vector<std::vector<std::string>> getRows(std::string CSVPath);
    CSV readCSV(std::string CSVPath);
    int writeCSV(std::string CSVPath, CSV csv);
    int mergeCSVs(std::string inputFolder, std::string outputFolder, std::vector<std::pair<std::string, std::vector<std::string>>> CSVPaths);

private:
    int splitText(std::vector<std::string> &ptr, std::string text, char delimiter);
};

#endif
