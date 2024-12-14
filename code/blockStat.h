#ifndef BLOCKSTAT_H
#define BLOCKSTAT_H


#include "mathAssign.h"
#include "stringAssign.h"
#include "printStat.h"

#include<vector>
#include <regex>
class BlockStatement 
{
    protected:
        PrintStatement myPrint;
        MathAssignmentStatement mathAssign;
        StringAssignmentStatement stringAssign;
        vector<string> ifBody;
        vector<string> elseBody;
    public:
        bool isItPrint(const string line);
        bool isItStringAssign(const string line);
        bool isItMathAssign(const string line);
        virtual void execute(vector<string>) = 0;        
};

#endif