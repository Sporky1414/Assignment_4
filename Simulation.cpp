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
  int currentClockTick = 1;
  stringstream inputConverter(inputHandler->readNextLine());
  int nextClockTickToAddStudents = 0;
  inputConverter >> nextClockTickToAddStudents;
  inputConverter.clear();
  cout << "Num of Windows: " << to_string(numOfWindows) << endl;
  bool continueLoop = true;
  Student *tempPointer = NULL;
  int numOfStudentsToAdd = 0;
  while(continueLoop) {
    cout << "CLOCK TICK: " << to_string(currentClockTick) << endl;
    cout << "CLOCK TICK TO ADD STUDENTS: " << to_string(nextClockTickToAddStudents) << endl;
    if(nextClockTickToAddStudents == currentClockTick) {
      inputConverter.str(inputHandler->readNextLine());
      inputConverter >> numOfStudentsToAdd;
      inputConverter.clear();
      cout << "NUM OF STUDENTS TO ADD: " << to_string(numOfStudentsToAdd) << endl;
      int neededClockTicks = 0;
      for(int i = 0; i < numOfStudentsToAdd; ++i) {
        inputConverter.str(inputHandler->readNextLine());
        inputConverter >> neededClockTicks;
        inputConverter.clear();
        cout << "NEEDS OF NEW STUDENT: " << neededClockTicks << endl;
        tempPointer = new Student(neededClockTicks);
        students->push(*tempPointer);
        cout << "STUDENT ADDED WITH NEEDS: " << tempPointer->getClockTicksNeeded() << endl;
      }
      if(inputHandler->inputHasDataLeft()) {
        inputConverter.str(inputHandler->readNextLine());
        inputConverter >> nextClockTickToAddStudents;
        inputConverter.clear();
      }
      cout << "AFTER STUDENTS ADDED: " << endl;;
      students->printQueue();
      cout << "\n\n";
    }

    for(int i = 0; i < numOfWindows; ++i) {
      if(windows[i]->isStudentPresent()) {
        cout << "STUDENT AT WINDOW " << to_string(i) << ": " << endl;
        windows[i]->printStudentAtWindow();
        windows[i]->incrementStudentUseTime();
        if(windows[i]->isStudentFinished()) {
          delete windows[i]->studentLeaves();
          if(!students->isEmpty()) {
            Student temp = (students->pop());
            Student* tempPointer = &temp;
            waitTimesOfAllStudents->append(tempPointer->getWaitTime());
            windows[i]->assignStudent(tempPointer);
          }
        }
      } else {
        if(!students->isEmpty()) {
          Student temp = (students->pop());
          Student* tempPointer = &temp;
          waitTimesOfAllStudents->append(tempPointer->getWaitTime());
          windows[i]->assignStudent(tempPointer);
        } else {
          windows[i]->incrementIdleTime();
        }
      }
    }
    cout << "QUEUE FOR AFTER STUDENTS SENT TO WINDOWS: " << endl;;
    students->printQueue();
    cout << "WINDOW STATUS AFTER NEW STUDENTS SENT TO WINDOWS: " << endl;
    for(int i = 0; i < numOfWindows; ++i) {
      if(windows[i]->isStudentPresent()) {
        cout <<"WINDOW " << to_string(i) << " HAS STUDENT: " << endl;
        windows[i]->printStudentAtWindow();
      } else {
        cout <<"WINDOW " << to_string(i) << " IS EMPTY." << endl;
      }
    }
    cout << "\n\n";

    Queue<Student>* temp = new Queue<Student>();
    for(int i = 0; i < students->getLength(); ++i) {
      Student tempStudent = students->pop();
      tempPointer = &tempStudent;
      if(i >= students->getLength() - numOfStudentsToAdd) {
        tempPointer->incrementWaitTime();
      }
      temp->push(*tempPointer);
    }
    students = temp;
    cout << "AFTER WAIT TIMES INCREASED FOR QUEUE STUDENTS" << endl;;
    students->printQueue();
    cout << "\n\n";

    ++currentClockTick;
    if(!inputHandler->inputHasDataLeft() && students->isEmpty()) {
      bool studentsPresetnAtWindows = false;
      for(int i = 0; i < numOfWindows; ++i) {
        if(windows[i]->isStudentPresent()) {
          studentsPresetnAtWindows = true;
          break;
        }
      }
      if(studentsPresetnAtWindows == false) {
        continueLoop = false;
      }
    }
  }
  return true;
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
  for(int i = 0; i < waitTimesOfAllStudents->getLength(); ++i) {
    sum += waitTimesOfAllStudents->valueAt(i);
  }
  double mean = sum/waitTimesOfAllStudents->getLength();
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

double Simulation::medianStudentWaitTime() {
  if(waitTimesOfAllStudents->getLength() % 2 == 0) {
    int secondPos = waitTimesOfAllStudents->getLength()/2;
    double firstPos = secondPos - 1;
    return (firstPos + secondPos)/2;
  } else {
    int midpoint = waitTimesOfAllStudents->getLength()/2;
    return waitTimesOfAllStudents->valueAt(midpoint);
  }
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
    if(waitTimesOfAllStudents->valueAt(i) >= 10) {
      ++studentCounter;
    }
  }
  return studentCounter;
}

int Simulation::windowIdleTimeOverFiveFinder() {
  int windowCounter = 0;
  for(int i = 0; i < numOfWindows; ++i) {
    if(windows[i]->getIdleTime() >= 5) {
      windowCounter++;
    }
  }
  return windowCounter;
}
