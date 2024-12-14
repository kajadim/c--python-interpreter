#ifndef IFSTATE_H
#define IFSTATE_H

#include "blockStat.h"
#include "globals.h"
#include "printStat.h"
#include "mathAssign.h"
#include "stringAssign.h"
#include "myException.h"
#include <string>
#include <vector>

using namespace std;

class IfStatement : public BlockStatement
{
    private:
        bool conditionMet;
        string condition;
        bool isThereElse = false;
    public:
        IfStatement();
        void setCondition(string);
        string extractCondition(const string&);
        int precedence(const string& );
        bool applyOperation(bool , bool , const string&);
        bool applyOperation(double , double , const string&);
        string applyOperation(string , string , const string& );
        vector<string> tokenize();
        bool  evaluateCondition();
        bool isDigit(const string&);
        void setIfBody(vector<string>);
        void setElseBody(vector<string>);
        void setIsThereElse(bool);
        void executeIf();
        void execute(vector<string>) override;
};
#endif
