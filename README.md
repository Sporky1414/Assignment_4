# Assignment_4

## Identifying Information:
1. AJ Keenan
1. Student ID: 2316808
1. akeenan@chapman.edu
1. CPSC 350-02
1. Assignment: Assignment 4

## Application Purpose
The purpose of this application is to simulate a registrar window. The simulation starts by taking in a file with the number of windows, when each students come (and how many at each time), and how long each student needs at the window. The program that runs through a simulation of the students waiting in line/going to windows/the windows waiting for students. After the simulation is complete, the program prints out the mean of the student wait times for the window, the median of those same wait times, the maximum student wait time, how many students waited over 10 minutes for service, the mean of the cumulative idle times of the windows, the maximum cumulative idle time among the windows, and how many windows sat idle for 5 minutes.

## Source Files
1. FileIO.h
1. FileIO.cpp
1. LinkedList.cpp
1. LinkedListNode.cpp
1. ListADT.h
1. main.cpp
1. Queue.cpp
1. Simulation.cpp
1. Simulation.h
1. Student.cpp
1. Student.h
1. Window.cpp
1. Window.h

## Known Errors:
There must be no extra spaces/lines in the file.

## References
1. Class Notes (Queue/LinkedList Implementation, Classes Needed)
1. ZyBooks (LinkedList functions/ListADT Implementation)
1. Stack Overflow (How to return NULL from a method in a Template Class, Convert Class Object to String, friend not allowed outside of a class definition, Qt c++ aggregate 'std::stringstream ss' has incomplete type and cannot be defined, 'bool operator<(Contact&)' must take exactly two arguments, Get the Object Pointer is Pointing To)
1. GeeksForGeeks (Pure Virtual Functions and Abstract Classes in C++, Passing Reference to a Pointer in C++)
1. TutorialsPoint (Relational Operators Overloading in C++, Input/Output Operators Overloading in C++)
1. Quora (How do I solve "taking address of temporary array" error in my code written in CPP?)
1. AppDividend (C++ Copy Constructor Example | Copy Constructor in C++)
1. C++ Reference (setprecision)

## Compilation Instructions
Use the "make all" command, courtesy of the included MAKEFILE, to compile all source files. To run the program, run the assignment4.exe program from any linux terminal, such as in docker. If you wish to pass through the file as a command line argument, please do so (after typing in the run command, type in the file path being used before hitting enter). However, it is not required to pass through the file path as an argument, since the program will ask for the path if one is not given (it is preferred if you do give one though).
