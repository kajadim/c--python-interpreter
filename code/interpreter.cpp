#include "interpreter.h"


Interpreter::Interpreter(const string &path) : parser(), fileReader(parser), filepath(path) {}

void Interpreter :: run() {
    fileReader.processFile(filepath);
}

