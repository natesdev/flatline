#include "csv.h"
#include <iostream>

void writeTestCSV();
void test(std::string, std::string, int);

int main()
{
    writeTestCSV();
    CSV example("example.csv");
    test(example.rows[0]["Name"], "John", 1);
    example.rows[0]["Name"] = "Jane";
    example.writeCSV();
    test(example.rows[0]["Name"], "Jane", 2);

    return 0;
}

void writeTestCSV()
{
    std::remove("example.csv"); // Remove existing csv that may have been modified from previous test
    CSV csv("example.csv");
    csv.addColumn("Name");
    csv.addColumn("Age");
    csv.addRow({"John", "24"});
    csv.writeCSV();
}

void test(std::string value, std::string expectedValue, int test)
{
    if (value == expectedValue)
    {
        std::cout << "\e[0;32mTest #" << test << " passed.\n";
    }
    else
    {
        std::cout << "\e[0;31mTest #" << test << " failed.\n";
    }
}