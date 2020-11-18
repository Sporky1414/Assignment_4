/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/

#include <iostream>
#include <fstream>

using namespace std;

//Class that holds the Students, and their timings.
class Student {
  public:
    //Constructors/Destructors
    Student();
    Student(int timeNeeded);
    Student(const Student &oldStudent);
    ~Student();

    //Increments the wait time and the clock ticks used variables.
    void incrementWaitTime();
    void incrementClockTicksAtWindow();

    //Getters for private variables.
    int getWaitTime();
    int getClockTicksUsed();
    int getClockTicksNeeded();
    bool isAtWindow();

    //Checks if a student is finished at the window.
    bool isFinishedAtWindow();
    //Sends a student to the window
    void goToWindow();
    //Takes a student from the window.
    void leaveWindow();

    //Override <<, to_string, ==, <, and > operators/functions
    friend ostream &operator<<(ostream &out, Student &student);
    friend string to_string(Student &student);
    bool operator ==(const Student& otherStudent);
    bool operator <(const Student& otherStudent);
    bool operator >(const Student& otherStudent);

  private:
    //Instance variables for waitTime, clockTicksUsed at window, clockTicksNeeded at window, and if the student is at a window.
    int waitTime;
    int clockTicksUsed;
    int clockTicksNeeded;
    bool atWindow;
};
