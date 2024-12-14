#ifndef PARSER_H
#define PARSER_H


#include "stringAssign.h"
#include "mathAssign.h"
#include "printStat.h"
#include "forStat.h"
#include "ifStat.h"
#include "variables.h"
#include "runException.h"
#include<vector>
#include<string>

class Parser
{
    private:
        MathAssignmentStatement mathAssign;
        StringAssignmentStatement stringAssign;
        ForStatement myFor;
        PrintStatement myPrint;
        IfStatement myIf;

        bool itIsFor = false;
        bool itIsIf = false;
        bool itIsElse = false;

        vector<string> forBody;
        vector<string> ifBody;
        vector<string> elseBody;
        

    public:
        Parser();
        void parseLine(string);
        bool isItFor(const string);
        bool isItPrint(const string);
        bool isItIf(const string);
        bool isItElse(const string);
        bool isItStringAssign(const string);
        bool isItMathAssign(const string);
};

#endif 


