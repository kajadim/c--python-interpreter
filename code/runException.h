#ifndef RUNEXCEPTION_H
#define RUNEXCEPTION_H

#include <stdexcept>

using namespace std;

class RunException : public exception
{
    public:
        RunException() {}
        friend ostream& operator<<(ostream& out, const RunException& e);

};

#endif