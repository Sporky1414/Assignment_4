/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/
#include "Window.h"
#include "Queue.cpp"
#include "FileIO.h"

using namespace std;

//Class that handles the simulation of the registrations.
class Simulation{
  public:
    //Constructors/Destructors
    Simulation();
    Simulation(string filePath);
    ~Simulation();

    //Runs the simulation.
    bool runSimulation();
    //Calculates the final results of the simulation and displays them.
    void calculateAndReturnFinalData();
    //Returns the value of numOfWindows
    int getNumOfWindows();

  private:
    //The queue of students waiting in line.
    Queue<Student>* students;
    //An array holding the windows being used.
    Window** windows;
    //Handles reading the file.
    FileIO* inputHandler;
    //Length of windows array.
    int numOfWindows;

    //ListADT that holds the wait times of all the students.
    ListADT<int>* waitTimesOfAllStudents;

    //Specific methods to calculate the mean/median/max of student wait times (and who waited over 10 minutes for a window)
    //And the mean/max of window idle times (and what windows were idle for over 5 minutes).
    double meanStudentWaitTime();
    double meanWindowIdleTime();
    int medianStudentWaitTime();
    int maxStudentWaitTime();
    int maxWindowIdleTime();
    int studentWaitOverTenFinder();
    int windowIdleTimeOverFiveFinder();
};
