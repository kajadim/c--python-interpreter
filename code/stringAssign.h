#ifndef STRINGASSIGN_H
#define STRINGASSIGN_H

#include "assignStat.h"

#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class StringAssignmentStatement : public AssignmentStatement
{
    public:
        StringAssignmentStatement();
        string evaluate();
        void addVariableToMap() override;
};

string operator*(const string&, int);
#endif