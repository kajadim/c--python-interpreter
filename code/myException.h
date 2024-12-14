#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <stdexcept>

using namespace std;

class MyException : public exception
{
    private:
        string message;

    public:
        MyException(string mess) : message(mess) {}

        virtual const char *what() const throw()
        {
            return message.c_str();
        }
};

#endif