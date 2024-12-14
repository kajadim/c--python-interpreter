
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string.h>
#include <fstream>

#include "parser.h"
#include "myException.h"
#include "runException.h"
using namespace std;

class Interpreter
{
    private:
        class FileReader {
            public:
                friend ostream& operator<<(ostream& out, const RunException& e)
                {
                    out << output;
                    out << endl;
                    return out;
                }
                Parser &parser;
                void processFile(const string &filePath)
                {
                    ifstream file(filePath); 
                    if (!file)
                    {
                        cerr << "Error opening file" << endl;
                        return;
                    }

                    string line;
                    while (getline(file, line))
                    { 
                        try
                        {
                            parser.parseLine(line);
                        }
                        catch(const MyException& me)
                        {
                            cout << output;
                            cout<< ">> " << me.what() << endl;
                            break;
                        }
                        catch(const RunException& re)
                        {
                            cout << re;
                            break;
                        }
                    }
                    file.close();
                }
                FileReader(Parser &p) : parser(p) {}
        };

        Parser parser;
        FileReader fileReader;
        const string & filepath;
    public:
        Interpreter(const string &);
        void run();

};

#endif