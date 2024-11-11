#ifndef MOD_H
#define MOD_H

#include <string>
#include <map>
#include <vector>

struct ValueModification
{
    std::string columnName;
    std::string newValue;
};

struct Exclusion
{
    enum class Mode
    {
        Exclude,
        Include
    } mode;
    std::vector<std::string> brawlers;
};

class Mod
{
public:
    std::string name;
    std::string path;

    std::map<std::string, std::map<std::string, ValueModification>> values;

    Exclusion exclusions;
};

#endif
