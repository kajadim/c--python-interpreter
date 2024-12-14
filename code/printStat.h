#ifndef PRINTSTAT_H
#define PRINTSTAT_H

#include "globals.h"
#include "myException.h"

#include<string>
#include<iostream>

using namespace std;

class PrintStatement
{
    public:
        PrintStatement();
        void addToOutput(string);
        bool isDigit(const string& );
        bool isVariable(const string&);
};

#endif