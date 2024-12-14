#include "ifStat.h"

#include <stack>
#include <regex>


IfStatement :: IfStatement () {}

void IfStatement :: setCondition (string cond)
{
    condition = extractCondition(cond);
}

string IfStatement :: extractCondition(const string& ifStatement)
{
    size_t start = ifStatement.find('f') + 1;
    if (start == string::npos)
    {
        throw MyException("Missing space before condition in 'if' statement.");
    }
    size_t end = ifStatement.find(':');
    if (end == string::npos)
    {
        throw runtime_error("Missing colon ':' after condition in 'if' statement.");
    }
    return ifStatement.substr(start, end - start); 
}

int IfStatement :: precedence(const string& op)
{
    if (op == ">" || op == "<" || op == "==" || op == "!=" || op == ">=" || op == "<=") return 1;
    if (op == "&&" || op == "||") return 0;
    return -1;
}


bool IfStatement::applyOperation(bool a, bool b, const string& op)
{
    if (op == "&&") return a && b;
    if (op == "||") return a || b;

    throw MyException("Unsupported operator for bool values");
}

bool IfStatement::applyOperation(double a, double b, const string& op)
{
    if (op == ">") return a > b;
    if (op == "<") return a < b;
    if (op == "==") return a == b;
    if (op == "!=") return a != b;
    if (op == ">=") return a >= b;
    if (op == "<=") return a <= b;

    throw MyException("Unsupported operator for numeric values");
}

string IfStatement::applyOperation(string a, string b, const string& op)
{
    
    string returnResult;
    if( ( a =="true" || a=="false") && (b=="true" || b=="false"))
    {
        bool var1, var2;
        if( a=="true") var1 = true;
        else var1 = false;

        if(b=="true") var2 = true;
        else var2=false;

        bool result = applyOperation(var1,var2,op);
        returnResult = result ? "true" : "false";
        return returnResult;
    }
    else if ( isDigit(a) && isDigit(b))
    {
        double var1, var2;
        var1 = stod(a);
        var2 = stod(b);
        bool result = applyOperation(var1,var2,op);
        returnResult = result ? "true" : "false";
        return returnResult;
    }
    throw MyException("Unsupported evaluation");
}

vector<string> IfStatement :: tokenize() 
{
    vector<std::string> tokens;
    string token;
    for (size_t i = 0; i < condition.length(); ++i) 
    {
        if (isspace(condition[i])) continue;

        if (condition[i] == '(' || condition[i] == ')')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, condition[i]));
        } 
        else if (condition.substr(i, 2) == "&&" || condition.substr(i, 2) == "||") 
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(condition.substr(i, 2));
            i += 1;
        }
        else if (condition.substr(i, 2) == ">=" || condition.substr(i, 2) == "<=" || condition.substr(i, 2) == "==" || condition.substr(i, 2) == "!=")
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(condition.substr(i, 2));
            i += 1;
        }
        else if (condition[i] == '>' || condition[i] == '<') 
        {
            if (!token.empty()) 
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, condition[i]));
        } 
        else 
        {
            token += condition[i];
        }
    }
    if (!token.empty()) 
    {
        tokens.push_back(token);
    }
    return tokens;
}

bool IfStatement ::  evaluateCondition() {

    std::stack<string> values;
    std::stack<std::string> ops;
    std::vector<std::string> tokens = tokenize();

    for (const string& token : tokens) 
    {
        if (token == "(") 
        {
            ops.push(token);
        } 
        else if (token == ")") 
        {
            while (!ops.empty() && ops.top() != "(") 
            {
                string val2 = values.top();
                values.pop();
                string val1 = values.top();
                values.pop();
                string op = ops.top();
                ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.pop();
        }
        else if (token == "&&" || token == "||")
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token))
            {
                string val2 = values.top(); 
                values.pop();
                string val1 = values.top(); 
                values.pop();
                string op = ops.top(); 
                ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(token);
        } 
        else if (token == ">" || token == "<" || token == "==" || token == "!=" || token == ">=" || token == "<=")
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token))
            {
                string val2 = values.top();
                values.pop();
                string val1 = values.top();
                values.pop();
                string op = ops.top(); 
                ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(token);
        }
        else 
        { 
            string value;
            auto doubleVar = doubles.findVariable(token);
            if (doubleVar) 
            {
                value = to_string( doubleVar->getValue());
            } 
            else
            {
                auto stringVar = strings.findVariable(token);
                if (stringVar)
                {
                    value = stringVar->getValue();
                } 
                else {
                    try
                    {
                        size_t pos;
                        double numValue = stod(token, &pos);
                        if (pos == token.length())
                        {
                            value = token ;
                        }
                        else
                        {
                            throw std::invalid_argument("Invalid token \n");
                        }
                    }
                    catch (const std::invalid_argument&)
                    {
                        if (token == "true")
                        {
                            value = "true";
                        }
                        else if (token == "false")
                        {
                            value = "false";
                        }
                        else
                        {
                            throw MyException("Variable, constant, or number not found \n");
                        }
                    }
                }
            }
            values.push(value);
        }
    }
    while (!ops.empty())
    {
        string val2 = values.top();
        values.pop();
        string val1 = values.top();
        values.pop();
        std::string op = ops.top();
        ops.pop();
        values.push(applyOperation(val1, val2, op));
    }
    return values.top() == "true" ? true : false ;
}

bool IfStatement :: isDigit(const string& str) 
{
    bool decimalPointSeen = false;

    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == '.')
        {
            if (decimalPointSeen)
            {
                return false;
            }
            decimalPointSeen = true;
        }
        else if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

void IfStatement :: setIfBody(vector<string> ifbody)
{
   ifBody = ifbody;
}

void IfStatement :: setElseBody(vector<string> elsebody)
{
    elseBody  = elsebody;
}

void IfStatement :: setIsThereElse(bool isElse)
{
    isThereElse = isElse;
}

void IfStatement :: executeIf()
{
    if(evaluateCondition()) 
    {
        execute(ifBody);
    }
    else if(isThereElse)
    {
        execute(elseBody);
    } 
}

void IfStatement :: execute(vector<string>body)
{
    
    for (const string& line : body)
    {
        if( isItPrint(line) ) 
        {
            myPrint.addToOutput(line);
        }
        else if(isItStringAssign(line) )
        {
            stringAssign.setBody(line);
            stringAssign.addVariableToMap();
        }
        else if(isItMathAssign(line) )
        {
            mathAssign.setBody(line);
            mathAssign.addVariableToMap();
        }
        else
        {
           throw MyException("Command not found \n");
        }
    }
}
