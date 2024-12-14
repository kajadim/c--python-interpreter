#include "forStat.h"
#include<regex>

#include "globals.h"

ForStatement :: ForStatement() {}

void ForStatement :: setRange (string line) 
{
    std::regex regex(R"(for\s+(\w+)\s+in\s+range\((\d+)\s*,\s*(\d+)\)\s*:\s*)");
    std::smatch match;

    regex_search(line, match, regex);

    iterator = match[1];
    start = stoi(match[2]);
    end = stoi(match[3]);
}

void ForStatement :: execute(vector<string> body)
{
    for(int i = start; i<end; i++)
    {
        Variable<double>* newVar = new Variable<double>(i, "i");
        doubles.addVariable(newVar);
        for (const auto& value : body) 
        {
            executeLine(value);
        }
    }
    
}

void ForStatement :: executeLine(string line)
{
    if( isItIf(line)) 
    {
        if(!ifBody.empty())
        {
            myIf.setIfBody(ifBody);
            myIf.executeIf();
        }
        if(!elseBody.empty())
        {
            myIf.setElseBody(elseBody);
            myIf.executeIf();
        }
        ifBody.clear();
        elseBody.clear();
        itIsIf = true;
        itIsElse = false;
        myIf.setCondition(line);  
        return;
    }
    else if( itIsIf && !itIsElse && isItElse(line)) 
    {
        myIf.setIfBody(ifBody);
        itIsElse = true;
        myIf.setIsThereElse(true);
        ifBody.clear();
        return;
    }
    else if ( itIsIf && !itIsElse && isItTabTab(line))
    {
        ifBody.push_back(line);
        return;
    }
    else if( itIsIf && itIsElse && isItTabTab(line) ) 
    {
        elseBody.push_back(line);
        return;
    }
    else if( itIsIf && itIsElse && !(isItTabTab(line)))
    {
        myIf.setElseBody(elseBody);
        myIf.executeIf();

        itIsElse = false;
        itIsIf = false;
        elseBody.clear();
        ifBody.clear();
        
    }
    else if( itIsIf && !itIsElse && !(isItTabTab(line)) )
    {
        myIf.setIfBody(ifBody);
        myIf.setIsThereElse(false);
        myIf.executeIf();
        itIsElse = false;
        itIsIf = false;
        ifBody.clear(); 
    }
    if( !itIsIf && !itIsElse && isItPrint(line)) 
    {
        myPrint.addToOutput(line);
    }
    else if(!itIsIf && !itIsElse && isItStringAssign(line) )
    {
        stringAssign.setBody(line);
        stringAssign.addVariableToMap();
    }
    else if( !itIsIf && !itIsElse && isItMathAssign(line) )
    {
        mathAssign.setBody(line);
        mathAssign.addVariableToMap();
    }
    else
    {
        throw MyException("for: Command not found \n"); 
    }
}

bool ForStatement :: isItIf (const string &line)
{
    //std::regex regex(R"(^\s*if\s+.+?\s*:\s*$)");
    std::regex regex(R"(^\s*if\s+.*?\s*:\s*$)");
    smatch match;

    return regex_search(line, match, regex);
}

bool ForStatement :: isItElse (const string & line)
{
    std::regex regex(R"(^\s*else\s*:\s*$)");
    smatch match;

    return regex_search(line, match, regex);
}

bool ForStatement :: isItTabTab(const string & line)
{
    if ( line.length()>= 8 && line[0]==' ' && line[1]==' ' && line[2]==' ' && line[3]==' ' && line[4]==' ' && line[5]==' ' && line[6]==' ' && line[7]==' ' ) 
    {
        return true;
    }
    return false;
}

