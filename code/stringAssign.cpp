#include "stringAssign.h"

StringAssignmentStatement::StringAssignmentStatement(){}

string  operator*(const string& str, int times) {
    string result;
    if( times == 0 )
    {
        throw MyException("Multiplying by zero is not allowed. \n");
    }
    for (int i = 0; i < times; ++i) {
        result += str;
    }
    return result;
}


string StringAssignmentStatement :: evaluate() 
{
    findVariableName();
    const string& expression = body;
    size_t equals_pos = expression.find('=');

    string expression_part = expression.substr(equals_pos + 1);
    istringstream stream(expression_part);
    string result;
    string current_string;

    while (stream >> ws && stream.peek() != EOF)
    {
        if (stream.peek() == '"')
        {
            stream.ignore();
            getline(stream, current_string, '"');
        }
        else if (isalpha(stream.peek())) 
        {
            string varName;
            while (isalnum(stream.peek()) || stream.peek() == '_')
            {
                varName += stream.get();
            }
            if (Variable<string>* varStr = strings.findVariable(varName))
            {
                current_string = varStr->getValue();
            }
            else
            {
                throw MyException("String:Undefined variable \n");
            }
        }
        else if (stream.peek() == '*')
        {
            stream.ignore();
            int times;
            stream >> times;
            current_string = current_string * times; // repeatString(current_string, times);
        }
        else if (stream.peek() == '+')
        {
            stream.ignore();
            result += current_string;
            current_string.clear();
        }
        else
        {
            throw MyException("Unexpected character: " + string(1, stream.peek()));
        }
    }
    result += current_string;

    return result;
}

void StringAssignmentStatement :: addVariableToMap ()
{
    string newValue = evaluate();
    if(doubles.findVariable(variableName))
    {
        doubles.removeVariable(variableName);
    }
    Variable<string>* newVar = new Variable<string>(newValue, variableName);
    strings.addVariable(newVar);
}