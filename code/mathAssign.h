#ifndef MATHASSIGN_H
#define MATHASSIGN_H

#include "assignStat.h"

#include <iostream>
#include <stack>
#include <string>
#include <cctype> 
#include <cstdlib>

using namespace std;

class MathAssignmentStatement : public AssignmentStatement
{
    public:
        MathAssignmentStatement();
        int precedence(char);
        double applyOperation(double, double, char );
        double evaluate();
        void addVariableToMap() override;
};
#endif

