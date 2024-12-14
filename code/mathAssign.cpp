#include"mathAssign.h"

MathAssignmentStatement :: MathAssignmentStatement() {}

int MathAssignmentStatement :: precedence(char op)
{ 
    if (op == '+' || op == '-') 
        return 1; 
    if (op == '*' || op == '/') 
        return 2; 
    return 0; 
} 

double MathAssignmentStatement :: applyOperation(double a, double b, char op)
{ 
    switch(op)
    { 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': 
            if( b == 0)
            {
                throw MyException("Dividing with zero is not allowed \n");
            }
            return a / b;
    } 
    return 0;
} 

double MathAssignmentStatement :: evaluate()
{ 
    findVariableName();
    stack<double> numbers;  
    stack<char> ops; 

    const string& expression = body;
    size_t equals_pos = expression.find('=');

    string tokens = expression.substr(equals_pos + 1);
    for (size_t i = 0; i < tokens.length(); ++i)
    {
        if (tokens[i] == ' ') 
            continue; 
        if (tokens[i] == '(')
        { 
            ops.push(tokens[i]); 
        } 
        else if (isdigit(tokens[i]) || (tokens[i] == '.' && isdigit(tokens[i+1])))
        { 
            double val = 0.0; 
            double decimalPlace = 0.1;
            bool decimal = false;

            while (i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.'))
            { 
                if (tokens[i] == '.')
                {
                    decimal = true;
                }
                else if (decimal)
                {
                    val += (tokens[i] - '0') * decimalPlace;
                    decimalPlace /= 10;
                }
                else
                {
                    val = (val * 10) + (tokens[i] - '0'); 
                }
                ++i; 
            } 
            --i;
            numbers.push(val); 
        }
        else if (isalpha(tokens[i]))
        {
            string varName;
            while (i < tokens.length() && (isalnum(tokens[i]) || tokens[i] == '_'))
            {
                varName += tokens[i];
                ++i;
            }
            --i;

            Variable<double>* var = doubles.findVariable(varName);
            if (var)
            {
                numbers.push(var->getValue());
            } 
            else
            {
                throw MyException("math:Undefined variable \n");
            }
        } 
        else if (tokens[i] == ')')
        { 
            while (!ops.empty() && ops.top() != '(')
            { 
                double val2 = numbers.top(); 
                numbers.pop(); 
                double val1 = numbers.top(); 
                numbers.pop(); 
                char op = ops.top(); 
                ops.pop(); 
                numbers.push(applyOperation(val1, val2, op)); 
            }
            if (ops.empty() || ops.top() != '(')
            {
                throw MyException("Mismatched parentheses");
            }
            ops.pop();
        } 
        else if (tokens[i] == '+' || tokens[i] == '-' || tokens[i] == '*' || tokens[i] == '/')
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i]))
            {
                if (numbers.size() < 2) {
                    throw MyException("Invalid expression: insufficient values for operation");
                }
                double val2 = numbers.top();
                numbers.pop();
                double val1 = numbers.top();
                numbers.pop();
                char op = ops.top();
                ops.pop();
                numbers.push(applyOperation(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
        else
        {
            throw MyException("Unexpected character: " + string(1, tokens[i]));
        }
    } 

    while (!ops.empty())
    {
        if (ops.top() == '(')
        {
            throw MyException("Mismatched parentheses");
        }
        if (numbers.size() < 2)
        {
            throw MyException("Invalid expression: insufficient values for operation");
        }
        double val2 = numbers.top(); 
        numbers.pop(); 
        double val1 = numbers.top(); 
        numbers.pop(); 
        char op = ops.top(); 
        ops.pop(); 
        numbers.push(applyOperation(val1, val2, op)); 
    } 

    return numbers.top(); 
}

void MathAssignmentStatement :: addVariableToMap ()
{
    double newValue = evaluate();
    if(strings.findVariable(variableName))
    {
        strings.removeVariable(variableName);
    }
    Variable<double>* newVar = new Variable<double>(newValue, variableName);
    doubles.addVariable(newVar);
    // doubles.iterateVariables();
}