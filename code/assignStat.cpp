#include "assignStat.h"
#include <cstddef>

void AssignmentStatement :: findVariableName() {
    size_t pos = 0;
    variableName = "";
    while (pos < body.size() && (body[pos] == ' ' || body[pos] == '\t'))
    {
        ++pos;
    }

    while (pos < body.size() && body[pos] != '=' && body[pos] != ' ')
    {
        variableName += body[pos];
        ++pos;
    }

}

string AssignmentStatement :: getVariableName()
{
    return variableName;
}

void AssignmentStatement :: setBody( string line)
{
    body = "";
    body=line;
}