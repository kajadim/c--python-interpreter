#ifndef FORSTAT_H
#define FORSTAT_H

#include "blockStat.h"
#include "ifStat.h"
#include "myException.h"
#include <string>
#include <stack>
#include <vector>

using namespace std;

class ForStatement : public BlockStatement
{
    private:
        string iterator;
        int start;
        int end;
        IfStatement myIf;
        bool itIsIf = false;
        bool itIsElse = false;
    public:
        ForStatement();
        void setRange(string);
        void execute(vector<string>) override;
        void executeLine(string);
        bool isItIf (const string &);
        bool isItElse (const string &);
        bool isItTabTab(const string &);
};

#endif