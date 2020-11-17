#include "Simulation.h"

Simulation::Simulation() {
  students = NULL;
  windows = NULL;
  inputHandler = NULL;
  waitTimesOfAllStudents = NULL;
  numOfWindows = 0;
}

Simulation::Simulation(string filePath) {
  waitTimesOfAllStudents = new LinkedList<int>();
  inputHandler = new FileIO(filePath);
  students = new Queue<Student>();
  string tempString = inputHandler->readNextLine();
  stringstream windowSizeFinder(tempString);
  numOfWindows = 0;
  windowSizeFinder >> numOfWindows;
  windows = new Window* [numOfWindows];
  for(int i = 0; i < numOfWindows; i++) {
    windows[i] = new Window();
  }
}

Simulation::~Simulation() {
  delete inputHandler;
  delete students;
  delete windows;
}

bool Simulation::runSimulation() {
  int numOfStudentsToAdd = 0;
  int currentClockTick = 0;
  string inputFromFileString = inputHandler->readNextLine();
  stringstream ss(inputFromFileString);
  int nextClockTickToAddStudents = 0;
  int prevClockTickToAddStudents = 0;
  Student* tempPointer = NULL;
  ss >> nextClockTickToAddStudents;
  bool allWindowsIdle = true;
  while(!students->isEmpty() || inputHandler->inputHasDataLeft() || !allWindowsIdle) {

    //Add new students to queue
    cout << "Clock Tick: " << to_string(currentClockTick) << endl;
    cout << "Clock Tick To Add Students: " << to_string(nextClockTickToAddStudents) << endl;
    if(currentClockTick == nextClockTickToAddStudents) {
      ss.clear();
      inputFromFileString = inputHandler->readNextLine();
      ss.str(inputFromFileString);
      ss >> numOfStudentsToAdd;
      int tempClockTicksNeeded = 0;
      for(int i = 0; i < numOfStudentsToAdd; ++i) {
        ss.clear();
        inputFromFileString = inputHandler->readNextLine();
        ss.str(inputFromFileString);
        ss >> tempClockTicksNeeded;
        Student* tempStudent = new Student(tempClockTicksNeeded);
        students->push(*tempStudent);
        cout << "\n";
      }
      cout << "\n";
      ss.clear();
      inputFromFileString = inputHandler->readNextLine();
      ss.str(inputFromFileString);
      prevClockTickToAddStudents = nextClockTickToAddStudents;
      ss >> nextClockTickToAddStudents;
    }


    for(int i = 0; i < numOfWindows; ++i) {
      cout << "WINDOW " << to_string(i) << " STATUS: ";
      if(windows[i]->isStudentPresent()) {
        windows[i]->incrementStudentUseTime();
        if(windows[i]->isStudentFinished()) {
          cout << "\nSTUDENT HAS FINISHED" << endl;
          windows[i]->studentLeaves();
          if(!students->isEmpty()) {
            tempPointer = new Student(students->pop());
            waitTimesOfAllStudents->append(tempPointer->getWaitTime());
            windows[i]->assignStudent(tempPointer);
            cout << "NEW STUDENT ARRIVES WITH FOLLOWING DETAILS: " << endl;
            windows[i]->printStudentAtWindow();
          } else {
            cout << "NOW IS EMPTY" << endl;
          }
        } else {
          cout << "STUDENT REMAINS WITH FOLLOWING INFO: " << endl;
          windows[i]->printStudentAtWindow();
        }
      } else {
        if(!students->isEmpty()) {
          cout << "BEING FILLED AFTER BEING IDLE" << endl;
          tempPointer = new Student(students->pop());
          waitTimesOfAllStudents->append(tempPointer->getWaitTime());
          windows[i]->assignStudent(tempPointer);
          cout << "NEW STUDENT ARRIVES WITH FOLLOWING DETAILS: " << endl;
          windows[i]->printStudentAtWindow();
        } else {
          cout << "WINDOW STILL IDLE. ";
          windows[i]->incrementIdleTime();
          cout << "NEW IDLE TIME: " << to_string(windows[i]->getIdleTime()) << endl;
        }
      }
    }
    int idleWindows = 0;
    for(int i = 0; i < numOfWindows; ++i) {
      cout << "WINDOW " << to_string(i) << " HAS A STUDENT PRESENT: " << to_string(windows[i]->isStudentPresent()) << endl;
      if(!windows[i]->isStudentPresent()) {
        ++idleWindows;
      }
    }
    if(idleWindows == numOfWindows) {
      allWindowsIdle = true;
    } else {
      allWindowsIdle = false;
    }
    cout << "BOTH WINDOWS IDLE: " << to_string(allWindowsIdle);

    Queue<Student>* tempQueue = new Queue<Student>();
    int counter = 0;
    while(!students->isEmpty()) {
      Student tempStudent = students->pop();
      tempPointer = &tempStudent;
      if(currentClockTick == prevClockTickToAddStudents) {
        if(counter < students->getLength() - numOfStudentsToAdd) {
          tempPointer->incrementWaitTime();
        }
      } else {
        tempPointer->incrementWaitTime();
      }
      tempQueue->push(*tempPointer);
      counter++;
      tempPointer = NULL;
    }
    while(!tempQueue->isEmpty()) {
      Student tempStudent = tempQueue->pop();
      tempPointer = &tempStudent;
      students->push(*tempPointer);
      tempPointer = NULL;
    }
    tempPointer = NULL;
    delete tempQueue;
    cout << "\nCURRENT STUDENT QUEUE: " << endl;
    students->printQueue();
    cout << "\n\n";
    ++currentClockTick;
  }
}

void Simulation::calculateAndReturnFinalData() {
  cout << "1. Mean Student Wait Time: " << to_string(meanStudentWaitTime()) << endl;
  cout << "2. Median Student Wait Time: " << to_string(medianStudentWaitTime()) << endl;
  cout << "3. Longest Student Wait Time: " << to_string(maxStudentWaitTime()) << endl;
  cout << "4. Number of Students Waiting Over Ten Minutes: " << to_string(studentWaitOverTenFinder()) << endl;
  cout << "5. Mean Window Idle Time: " << to_string(meanWindowIdleTime()) << endl;
  cout << "6. Longest Window Idle Time: " << to_string(maxWindowIdleTime()) << endl;
  cout << "7. Number of Windows Idle For Over Five Minutes: " << to_string(windowIdleTimeOverFiveFinder()) << endl;
}

double Simulation::meanStudentWaitTime() {
  double sum = 0;
  int numOfZeroes = 0;
  cout << "WAIT TIME LIST: " << to_string(waitTimesOfAllStudents->isEmpty()) << endl;
  if(waitTimesOfAllStudents->isEmpty()) {
    return 0;
  }
  for(int i = 0; i < waitTimesOfAllStudents->getLength(); ++i) {
    int value = waitTimesOfAllStudents->valueAt(i);
    if(value == 0) {
      ++numOfZeroes;
    } else {
      sum += waitTimesOfAllStudents->valueAt(i);
    }
  }
  if(numOfZeroes == waitTimesOfAllStudents->getLength()) {
    return 0;
  }
  double mean = sum/(waitTimesOfAllStudents->getLength() - numOfZeroes);
  return mean;
}

double Simulation::meanWindowIdleTime() {
  double sum = 0;
  for(int i = 0; i < numOfWindows; ++i) {
    sum += windows[i]->getIdleTime();
  }
  double mean = sum/numOfWindows;
  return mean;
}

int Simulation::medianStudentWaitTime() {
  int midpoint = waitTimesOfAllStudents->getLength()/2;
  return waitTimesOfAllStudents->valueAt(midpoint);
}

int Simulation::maxStudentWaitTime() {
  int max = 0;
  for(int i = 0; i < waitTimesOfAllStudents->getLength(); ++i) {
    int valueAtI = waitTimesOfAllStudents->valueAt(i);
    if(valueAtI >= max) {
      max = valueAtI;
    }
  }
  return max;
}

int Simulation::maxWindowIdleTime() {
  int max = 0;
  for(int i = 0; i < numOfWindows; ++i) {
    if(windows[i]->getIdleTime() >= max) {
      max = windows[i]->getIdleTime();
    }
  }
  return max;
}

int Simulation::studentWaitOverTenFinder() {
  int studentCounter = 0;
  for(int i = 0; i < waitTimesOfAllStudents->getLength(); ++i) {
    if(waitTimesOfAllStudents->valueAt(i) > 10) {
      ++studentCounter;
    }
  }
  return studentCounter;
}

int Simulation::windowIdleTimeOverFiveFinder() {
  int windowCounter = 0;
  for(int i = 0; i < numOfWindows; ++i) {
    if(windows[i]->getIdleTime() > 5) {
      windowCounter++;
    }
  }
  return windowCounter;
}
