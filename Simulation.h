#include "Window.h"
#include "Queue.cpp"
#include "FileIO.h"

using namespace std;

class Simulation{
  public:
    Simulation();
    Simulation(string filePath);
    ~Simulation();

    bool runSimulation();
    void calculateAndReturnFinalData();
    int getNumOfWindows();

  private:
    Queue<Student>* students;
    Window** windows;
    FileIO* inputHandler;
    int numOfWindows;

    ListADT<int>* waitTimesOfAllStudents;

    double meanStudentWaitTime();
    double meanWindowIdleTime();
    double medianStudentWaitTime();
    int maxStudentWaitTime();
    int maxWindowIdleTime();
    int studentWaitOverTenFinder();
    int windowIdleTimeOverFiveFinder();
};
