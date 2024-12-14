#include "parser.h"

#include <regex>

using namespace std;

Parser :: Parser() {}

void Parser :: parseLine(string line) 
{
    if(line=="run")
    {
        if(!forBody.empty())
        {
            myFor.execute(forBody);
        }
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

        throw RunException();
    }
    if ( isItFor(line))
    {
        if(!forBody.empty())
        {
            itIsFor = false;
            myFor.execute(forBody);
            forBody.clear();
        }
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
        itIsIf = false;
        itIsElse = false;

        itIsFor = true;
        myFor.setRange(line);

        return;
    }
    else if( itIsFor && sizeof(line) >= 4 && line[0]==' ' && line[1]==' ' && line[2]==' ' && line[3]==' ')
    {
        forBody.push_back(line);
        return;
    }
    else if(itIsFor && !(sizeof(line) >= 4 && line[0]==' ' && line[1]==' ' && line[2]==' ' && line[3]==' '))
    {
        itIsFor = false;
        myFor.execute(forBody);
        forBody.clear();
    }
    if( isItIf(line))
    {
        if(!forBody.empty())
        {
            itIsFor = false;
            myFor.execute(forBody);
            forBody.clear();
        }
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
    else if ( itIsIf && !itIsElse && line.length()>= 4 && line[0]==' ' && line[1]==' ' && line[2]==' ' && line[3]==' ')
    {
        ifBody.push_back(line);
        return;
    }
    else if( itIsIf && itIsElse && line.length() >= 4 && line[0]==' ' && line[1]==' ' && line[2]==' ' && line[3]==' ' )
    {
        elseBody.push_back(line);
        return;
    }
    else if( itIsIf && itIsElse && !(line.length()>= 4 && line[0]==' ' && line[1]==' ' && line[2]==' ' && line[3]==' ' ))
    {
        myIf.setElseBody(elseBody);
        myIf.executeIf();

        itIsElse = false;
        itIsIf = false;
        elseBody.clear();
        ifBody.clear();
        
    }
    else if( itIsIf && !itIsElse && !(line.length()>= 4 && line[0]==' ' && line[1]==' ' && line[2]==' ' && line[3]==' ') ) // posle if-a nije bilo else
    {
        myIf.setIfBody(ifBody);
        myIf.setIsThereElse(false);
        myIf.executeIf();
        itIsElse = false;
        itIsIf = false;
        ifBody.clear();
    }
   
    if( !itIsFor && !itIsIf && !itIsElse && isItPrint(line)) 
    {
        myPrint.addToOutput(line);
    }
    else if(!itIsFor && !itIsIf && !itIsElse && isItStringAssign(line) )
    {
        stringAssign.setBody(line);
        stringAssign.addVariableToMap();
    }
    else if(!itIsFor && !itIsIf && !itIsElse && isItMathAssign(line) )
    {
        mathAssign.setBody(line);
        mathAssign.addVariableToMap();
    }
    else
    {
        throw MyException("parser: Command not found \n"); 
    }
}

bool Parser :: isItFor(const string line)
{
    regex regex(R"(for\s+(\w+)\s+in\s+range\((\d+)\s*,\s*(\d+)\)\s*:\s*)");
    smatch match;

    return regex_search(line, match, regex);
}

bool Parser :: isItPrint(const string line)
{
    regex regex(R"(print\s*\(\s*(?:(['"])(.*?)\1|(\d+(\.\d+)?)|(\w+))\s*\))");
    smatch match;

    return regex_search(line, match, regex);
}

bool Parser :: isItIf (const string line)
{
    //std::regex regex(R"(^\s*if\s+.+?\s*:\s*$)");
    // regex regex(R"(^\s*if\s+.*?\s*:\s*$)");
    regex regex(R"(if\s+.*?\s*:\s*$)");

    smatch match;

    return regex_search(line, match, regex);
}

bool Parser :: isItElse (const string line)
{
    // regex regex(R"(^\s*else\s*:\s*$)");
    regex regex(R"(else\s*:\s*$)");
    smatch match;

    return regex_search(line, match, regex);
}

bool Parser :: isItStringAssign(const string line)
{
    //std::regex regex(R"(^(\w+)\s*=\s*(.*)$)");
    // regex regex(R"(^\s*(\w+)\s*=\s*(.*)$)");
    regex regex(R"((\w+)\s*=\s*(.*)$)");
    smatch match;

    return regex_search(line, match, regex) && line.find('\"') != std::string::npos;
}
bool Parser :: isItMathAssign(const string line)
{
    //std::regex regex(R"(^(\w+)\s*=\s*(.*)$)");
    // std::regex regex(R"(^(\w+)\s*=\s*[^\s].*)");
    // regex regex(R"(^\s*(\w+)\s*=\s*(.*)$)");
    regex regex(R"((\w+)\s*=\s*(.*)$)");
    smatch match;

    return regex_search(line, match, regex) && line.find('\"') == std::string::npos;
}