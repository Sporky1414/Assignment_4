/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/

#include "Window.h"

//Constructor: Sets studentPresent pointer to null, that there are no students present, and that the window has a current idle time of 0.
Window::Window() {
  studentPresent = false;
  studentAtWindow = NULL;
  idleTime = 0;
}

//Destructor: Empty constructor.
Window::~Window() {
  //Not deleting student should the window be deleted, since that could cause problems elsewhere.
  //As a result, nothing needs to be done here. Student is deleted in simulation.
}

//Getter for studentPresent
bool Window::isStudentPresent() {
  return studentPresent;
}

//Sets studentAtWindow to the pointer passed as an argument. Sets studentPresent to true.
void Window::assignStudent(Student* newStudent) {
  studentAtWindow = newStudent;
  studentPresent = true;
}

//Sets studentAtWindow to NULL and studentPresent to false. The student leaving is returned.
Student* Window::studentLeaves() {
  Student* temp = studentAtWindow;
  studentAtWindow = NULL;
  studentPresent = false;
  return temp;
}

//Getter for idleTime
int Window::getIdleTime() {
  return idleTime;
}

//Increments idleTime by 1
void Window::incrementIdleTime() {
  ++idleTime;
}

//Calls incrementClockTicksAtWindow of studentAtWindow
void Window::incrementStudentUseTime() {
  studentAtWindow->incrementClockTicksAtWindow();
}

//Returns the value of isFinishedAtWindow from studentAtWindow
bool Window::isStudentFinished() {
  return studentAtWindow->isFinishedAtWindow();
}

//Prints the data of the student at the window.
void Window::printStudentAtWindow() {
  cout << to_string(*studentAtWindow);
}
