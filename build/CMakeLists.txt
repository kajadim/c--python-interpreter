cmake_minimum_required(VERSION 3.10)
project(mojProjekat)
SET(CMAKE_CXX_STANDARD 14)
SET (SRC_FILES 
    ../code/main.cpp
    ../code/globals.cpp
    ../code/assignStat.cpp
    ../code/mathAssign.cpp
    ../code/stringAssign.cpp
    ../code/printStat.cpp
    ../code/blockStat.cpp
    ../code/ifStat.cpp
    ../code/forStat.cpp
    ../code/parser.cpp
    ../code/interpreter.cpp
)
add_executable(exe ${SRC_FILES})