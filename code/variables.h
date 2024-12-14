#ifndef VARIABLES_H
#define VARIABLES_H

#include "variable.h"

#include <map>
#include <iostream>

using namespace std;

template<typename T>
class Variables {
    private:
        map<string, Variable<T>* > variables;
    public:
        Variables();
        ~Variables();
        Variable<T>* findVariable(const string&) const;
        void addVariable(Variable<T>*);
        void removeVariable(string);
        void iterateVariables() const;
};

template<typename T>
Variables<T> :: Variables() {}

template<typename T>
Variables<T>::~Variables()
{
    for (auto& it : variables) {
        delete it.second;
    }
    variables.clear();
}

template<typename T>
Variable<T>* Variables<T>::findVariable(const string& name) const 
{
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    return nullptr;
}

template<typename T>
void Variables<T>::addVariable(Variable<T>* v)
{
    auto existingVar = findVariable(v->getName());
    if (existingVar)
    {
        existingVar->setValue(v->getValue());  
    }
    else
    {
        variables[v->getName()] = v;
    }
}

template<typename T>
void Variables<T>::removeVariable(string name)
{
   
    auto it = variables.find(name);
    if (it != variables.end())
    {
        delete it->second;    
        variables.erase(it); 
    }
}

template<typename T>
void Variables<T>::iterateVariables() const
{
    cout << "Iteration throught variables:" << endl;
    for (auto it = variables.begin(); it != variables.end(); ++it)
    {
        cout << "Variable Name: " << it->first << endl;
        cout << "Variable Value: " << it->second->getValue() << endl;
    }
}

#endif