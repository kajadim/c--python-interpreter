#include "blockStat.h"

bool BlockStatement :: isItPrint(const string line)
{
    regex regex(R"(^\s*print\s*\(\s*(?:(['"])(.*?)\1|(\d+(\.\d+)?)|(\w+))\s*\))");
    smatch match;

    return regex_search(line, match, regex);
}
bool BlockStatement :: isItStringAssign(const string line)
{
    //regex regex(R"(^(\w+)\s*=\s*(.*)$)");
    regex regex(R"(^\s*(\w+)\s*=\s*(.*)$)");
    smatch match;

    return regex_search(line, match, regex) && line.find('\"') != std::string::npos;
}
bool BlockStatement :: isItMathAssign(const string line)
{
    //regex regex(R"(^(\w+)\s*=\s*(.*)$)");
    regex regex(R"(^\s*(\w+)\s*=\s*(.*)$)");
    smatch match;

    return regex_search(line, match, regex) && line.find('\"') == std::string::npos;
}
