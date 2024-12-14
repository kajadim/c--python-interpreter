#include "printStat.h"
#include <cctype>
#include <regex>

using namespace std;

PrintStatement :: PrintStatement () {}


void PrintStatement :: addToOutput (string newLine)
{
   int index;
   for(int i=0; i<newLine.length(); i++)
   {
        if(newLine[i]=='p')
        {
            index = i;
            break;
        }
   }
   string body = newLine.substr(6+index,newLine.length() - 7-index);
  
   if(body[0]=='\"' && body[body.length() - 1]=='\"') 
   {
        output+= ">> " + body.substr(1,body.length()-2)+"\n";
   }
   else if(isDigit(body)) 
   {
        output+= ">> " + body+"\n";
   }
   else if(isVariable(body))
   {
        if(doubles.findVariable(body)!=nullptr)
        {
            output+= ">> " + to_string(doubles.findVariable(body)->getValue())+"\n";
        }
        else if(strings.findVariable(body)!=nullptr)
        {
            output+= ">> " + strings.findVariable(body)->getValue()+"\n";
        }
        else
        {
            throw MyException("print: Undefined variable \n");
        }
   }
   else
   {
        throw MyException("Invalid expression: insufficient values for operation");
   }
}

bool PrintStatement :: isDigit(const string& str)
{
    for (char c : str)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return true;
}

bool PrintStatement :: isVariable(const string& str)
{
    regex regex(R"([a-zA-Z][0-9]*)");
    smatch match;

    return regex_search(str, match, regex);
}
