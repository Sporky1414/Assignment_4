/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/

#include "Student.h"
#include <sstream>

//Constructor: Default constructor where all times are 0 and the student is not at a window.
Student::Student() {
  waitTime = 0;
  clockTicksUsed = 0;
  clockTicksNeeded = 0;
  atWindow = false;
}

//Constructor: Sets wait time and clockTicksUsed to 0 while setting clockTicksNeeded to the argument. atWindow is also false.
Student::Student(int timeNeeded) {
  waitTime = 0;
  clockTicksUsed = 0;
  clockTicksNeeded = timeNeeded;
  atWindow = false;
}

//Constructor: Copies data from oldStudent to new student.
Student::Student(const Student &oldStudent) {
  waitTime = oldStudent.waitTime;
  clockTicksUsed = oldStudent.clockTicksUsed;
  clockTicksNeeded = oldStudent.clockTicksNeeded;
  atWindow = oldStudent.atWindow;
}

//Destructor: Nothing is done here since no pointers/objects are used.
Student::~Student() {}

//Increments waitTime by 1.
void Student::incrementWaitTime() {
  ++waitTime;
}

//Increments clockTicksUsed by 1.
void Student::incrementClockTicksAtWindow() {
  ++clockTicksUsed;
}

//Getter for waitTime
int Student::getWaitTime() {
  return waitTime;
}

//Getter for clockTicksUsed
int Student::getClockTicksUsed() {
  return clockTicksUsed;
}

//Getter for clockTicksNeeded
int Student::getClockTicksNeeded() {
  return clockTicksNeeded;
}

//Getter for atWindow
bool Student::isAtWindow() {
  return atWindow;
}

//Returns if clockTicksUsed = clockTicksNeeded (Student has spent all time needed at window)
bool Student::isFinishedAtWindow() {
  return clockTicksUsed == clockTicksNeeded;
}

//Sets atWindow to true
void Student::goToWindow() {
  atWindow = true;
}

//Sets atWindow to false
void Student::leaveWindow() {
  atWindow = false;
}

//Overrides << to print out all numerical data from student.
ostream& operator<<(ostream &out, Student &student) {
  out << "Wait Time: " << to_string(student.getWaitTime()) << "\nClockTicksUsed: " << to_string(student.getClockTicksUsed()) << "\nClockTicksNeeded: " << to_string(student.getClockTicksNeeded()) << endl;
  return out;
}

//Overrides to_string to use the string made in the override of <<
string to_string(Student &student) {
  ostringstream ss;
  ss << student;
  return ss.str();
}

//Overrides == so each of the numerical instance variables must equal each other for the student ot be equal.
bool Student::operator ==(const Student& otherStudent) {
  return (waitTime == otherStudent.waitTime && clockTicksUsed == otherStudent.clockTicksUsed && clockTicksNeeded == otherStudent.clockTicksNeeded);
}

//Overrides < so a student is less than another student should all the numerical values added together be less than all the numerical values added together of otherStudent.
bool Student::operator <(const Student& otherStudent) {
  return waitTime + clockTicksUsed + clockTicksNeeded < otherStudent.waitTime + otherStudent.clockTicksUsed + otherStudent.clockTicksNeeded;
}

//Overrides > so a student is greater than another student should all the numerical values added together be greater than all the numerical values added together of otherStudent.
bool Student::operator >(const Student& otherStudent) {
  return waitTime + clockTicksUsed + clockTicksNeeded > otherStudent.waitTime + otherStudent.clockTicksUsed + otherStudent.clockTicksNeeded;
}
