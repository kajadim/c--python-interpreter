#include<iostream>
using namespace std;

#include "interpreter.h"
int main()
{
    cout<<"enter file path:"<<endl;
    string filePath;
    cin>>filePath;
    Interpreter interpreter(filePath);
    interpreter.run();
}