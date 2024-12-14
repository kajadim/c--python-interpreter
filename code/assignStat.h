#ifndef ASSIGNSTAT_H
#define ASSIGNSTAT_H

#include "myException.h"
#include "globals.h"

#include <string>

using namespace std;

class AssignmentStatement
{
    protected:
        string body;
        string variableName;
    public:
        void findVariableName();
        string getVariableName();
        void setBody(string);
        virtual void addVariableToMap() = 0;
};

#endif