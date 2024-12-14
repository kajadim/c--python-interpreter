#ifndef VARIABLE_H
#define VARIABLE_H

#include <typeinfo>
#include <type_traits>
#include <string>

using namespace std;


template<typename T>
class Variable {
    private:
        const string name;
        T value;
    public:
        Variable(T,string);
        void setValue(T);
        T getValue() const;
        string getName() const;
};

template<typename T>
Variable<T> :: Variable( T v, const string n) : value(v), name(n) {}

template<typename T>
T Variable<T> :: getValue() const
{
    return value;
}

template<typename T>
void Variable<T> :: setValue(T t)
{
    value=t;
}

template<typename T>
string Variable<T> :: getName() const
{
    return name;
}

#endif