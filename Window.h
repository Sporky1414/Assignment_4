/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/
#include "Student.h"

using namespace std;

//Class to hold a registration window, which includes any students present and how long a window is idle.
class Window {
  public:
    //Constructor/Destructor
    Window();
    ~Window();

    //Getter for studentPresent instance variable
    bool isStudentPresent();
    //Getter for idleTime
    int getIdleTime();

    //Assigns a student to this window.
    void assignStudent(Student* newStudent);
    //Remove the student from the window, but return a pointer to the student object.
    Student* studentLeaves();

    //Increments window idle time.
    void incrementIdleTime();
    //Increments the student's usage time instance variable.
    void incrementStudentUseTime();
    //Determines if a student has finished what they need to at the window.
    bool isStudentFinished();
    //Print the data of the student at the window.
    void printStudentAtWindow();

  private:
    //Tells if a student is present at the window.
    bool studentPresent;
    //Instance variable for how long a window is idle cumulatively in the simulation.
    int idleTime;
    //Pointer to the student currently at the window.
    Student* studentAtWindow;
};
