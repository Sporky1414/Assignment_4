/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/
#include "Simulation.h"
#include <iomanip>

//Constructor: Default constructor where all pointers are set to NULL and no windows are present.
Simulation::Simulation() {
  students = NULL;
  windows = NULL;
  inputHandler = NULL;
  waitTimesOfAllStudents = NULL;
  numOfWindows = 0;
}

//Constructor: Preps the simulation from the filePath passed as an argument.
Simulation::Simulation(string filePath) {
  //Creates a LinkedList to hold all the student wait times
  waitTimesOfAllStudents = new LinkedList<int>();
  //Initializes the inputHandler with the filePath. Will account for if the file or filepath are in the wrong format or invalid, respectively.
  inputHandler = new FileIO(filePath);
  //Initializes the queue of students.
  students = new Queue<Student>();
  //Reads the first line of the file (number of windows) and stores it in numOfWindows.
  string tempString = inputHandler->readNextLine();
  stringstream windowSizeFinder(tempString);
  numOfWindows = 0;
  windowSizeFinder >> numOfWindows;
  //Creates an array of windows with length numOfWindows.
  windows = new Window* [numOfWindows];
  for(int i = 0; i < numOfWindows; i++) {
    windows[i] = new Window();
  }
}

//Deletes the inputHandler, students queue, waittimes list, and windows array.
Simulation::~Simulation() {
  delete waitTimesOfAllStudents;
  delete inputHandler;
  delete students;
  delete windows;
}

//Runs the simulation. Returns true should it finish without problems.
bool Simulation::runSimulation() {
  //Sets variables for number of students to add, the clock tick, a string that will get data from the input file,
  //a stringstream to convert the string to an int, the next clock tick to add students, the previous clock tick where
  //students were added, a pointer to a student for copying purposes, and a boolean for if the windows are all idle.
  int numOfStudentsToAdd = 0;
  int currentClockTick = 0;
  //Takes in the first clock tick to add students from the file.
  string inputFromFileString = inputHandler->readNextLine();
  stringstream ss(inputFromFileString);
  int nextClockTickToAddStudents = 0;
  int prevClockTickToAddStudents = 0;
  Student* tempPointer = NULL;
  ss >> nextClockTickToAddStudents;
  bool allWindowsIdle = true;
  //Runs simulation until the student queue is exhausted, the input file has been read through, and all the windows are idle (no more students present)
  while(!students->isEmpty() || inputHandler->inputHasDataLeft() || !allWindowsIdle) {
    //PART 1: ADD STUDENTS TO QUEUE:
    //If the current clock tick matches the clock tick to add students, students will be added to the queue. Otherwise, skip part 1.
    if(currentClockTick == nextClockTickToAddStudents) {
      //Get the number of students to be added from the file.
      ss.clear();
      inputFromFileString = inputHandler->readNextLine();
      ss.str(inputFromFileString);
      ss >> numOfStudentsToAdd;
      //Set a temp variable to hold the data from the file, which holds how long each student needs at the window.
      int tempClockTicksNeeded = 0;
      //Adds each student to the queue until all students have been added (determined by numOfStudentsToAdd).
      for(int i = 0; i < numOfStudentsToAdd; ++i) {
        //Takes in clockTicksNeeded for this student from the file.
        ss.clear();
        inputFromFileString = inputHandler->readNextLine();
        ss.str(inputFromFileString);
        ss >> tempClockTicksNeeded;
        //Creates a new student from tempClockTicksNeeded
        Student* tempStudent = new Student(tempClockTicksNeeded);
        //Adds student to the queue.
        students->push(*tempStudent);
      }
      //Set nextClockTickToAddStudents to the next line in the file, should there be more data.
      //Before switching nextClockTickToAddStudents, it's old value is set to prevClockTickToAddStudents for future use.
      ss.clear();
      inputFromFileString = inputHandler->readNextLine();
      ss.str(inputFromFileString);
      prevClockTickToAddStudents = nextClockTickToAddStudents;
      ss >> nextClockTickToAddStudents;
    }

    //PART 2: ASSIGN STUDENTS TO WINDOWS/INCREASE WINDOW IDLE TIME/REMOVE STUDENTS FROM WINDOW IF FINISHED.
    //Iterate through each window in the array.
    for(int i = 0; i < numOfWindows; ++i) {
      if(windows[i]->isStudentPresent()) {
        //If a student is present, increment their use time.
        windows[i]->incrementStudentUseTime();
        if(windows[i]->isStudentFinished()) {
          //If a student is finished at the window, remove them from the window.
          delete (windows[i]->studentLeaves());
          if(!students->isEmpty()) {
            //If there are students in the queue, assign them to the window and remove that student from the queue.
            //Add how long the student waited to the waitTimesOfAllStudents list.
            tempPointer = new Student(students->pop());
            waitTimesOfAllStudents->append(tempPointer->getWaitTime());
            windows[i]->assignStudent(tempPointer);
          }
        }
      } else {
        //Student is not present at the window.
        if(!students->isEmpty()) {
          //If there are students in the queue, assign them to the window and remove that student from the queue.
          //Add how long the student waited to the waitTimesOfAllStudents list.
          tempPointer = new Student(students->pop());
          waitTimesOfAllStudents->append(tempPointer->getWaitTime());
          windows[i]->assignStudent(tempPointer);
        } else {
          //If the queue is empty, increase the window's cumulative idle time.
          windows[i]->incrementIdleTime();
        }
      }
    }
    //Count how many idle windows there are.
    int idleWindows = 0;
    for(int i = 0; i < numOfWindows; ++i) {
      if(!windows[i]->isStudentPresent()) {
        ++idleWindows;
      }
    }
    //If all windows are idle, allWindowsIdle becomes true. Otherwise, it becomes false.
    if(idleWindows == numOfWindows) {
      allWindowsIdle = true;
    } else {
      allWindowsIdle = false;
    }

    //PART 3: INCREMENT STUDENT WAIT TIMES
    //Create a temp queue to hold students as their wait times are incremented, since the students can not be updated without removing them from
    //the main queue first.
    Queue<Student>* tempQueue = new Queue<Student>();
    //Counter helps for determining which students were just added and do not need their wait times increased yet.
    int counter = 0;
    //Iterate through students until all studnets have been moved to tempQueue.
    while(!students->isEmpty()) {
      //Pop the data from students to a tempStudent reference, which is then pointed to a pointer.
      Student tempStudent = students->pop();
      tempPointer = &tempStudent;
      //If students were just added during the clock tick, these two will match, meaning students are present whose wait times will not increase.
      if(currentClockTick == prevClockTickToAddStudents) {
        if(counter < students->getLength() - numOfStudentsToAdd) {
          //If the student was not just added, their wait time will be incremented.
          tempPointer->incrementWaitTime();
        }
      } else {
        //Since no students were added, all students will have their wait times incremented.
        tempPointer->incrementWaitTime();
      }
      //Push the student to the temp queue, increase the counter, and reset tempPointer.
      tempQueue->push(*tempPointer);
      counter++;
      tempPointer = NULL;
    }
    //Once all students have had their wait times incremented, copy everything back to students from tempQueue.
    while(!tempQueue->isEmpty()) {
      Student tempStudent = tempQueue->pop();
      tempPointer = &tempStudent;
      students->push(*tempPointer);
      tempPointer = NULL;
    }
    //Set tempPointer to NULL, delete tempQueue.
    tempPointer = NULL;
    delete tempQueue;

    //Increment the clock tick to start again.
    ++currentClockTick;
  }
  //Return true, since simulation finished.
  return true;
}

//Calculates/prints the final data from the simulation.
void Simulation::calculateAndReturnFinalData() {
  //Determines the number to passed through setprecission such that two decimals are printed for meanStudentWaitTime.
  int precisionNum = 0;
  double mean = meanStudentWaitTime();
  int testNum = (int) mean;
  while(testNum > 0) {
    testNum = testNum/10;
    ++precisionNum;
  }
  //After the precision number is found (number of whole number digits), 2 is added to account for the two decimal places.
  precisionNum += 2;
  //Prints the required data regarding student wait times.
  cout << "1. Mean Student Wait Time: " << setprecision(precisionNum) << mean << endl;
  cout << "2. Median Student Wait Time: " << medianStudentWaitTime() << endl;
  cout << "3. Longest Student Wait Time: " << maxStudentWaitTime() << endl;
  cout << "4. Number of Students Waiting Over Ten Minutes: " << studentWaitOverTenFinder() << endl;
  //Determines the number to passed through setprecission such that two decimals are printed for meanWindowIdleTime.
  precisionNum = 0;
  mean = meanWindowIdleTime();
  testNum = (int) mean;
  while(testNum > 0) {
    testNum = testNum/10;
    ++precisionNum;
  }
  //After the precision number is found (number of whole number digits), 2 is added to account for the two decimal places.
  precisionNum += 2;
  //Prints data from the window idle times.
  cout << "5. Mean Window Idle Time: " << setprecision(precisionNum) << mean << endl;
  cout << "6. Longest Window Idle Time: " << maxWindowIdleTime() << endl;
  cout << "7. Number of Windows Idle For Over Five Minutes: " << windowIdleTimeOverFiveFinder() << endl;
}

//Returns a double holding the mean of the student wait times.
double Simulation::meanStudentWaitTime() {
  //Variables to hold the sum of the wait times and the number of 0 wait times.
  double sum = 0;
  int numOfZeroes = 0;
  if(waitTimesOfAllStudents->isEmpty()) {
    //No one waited, so zero is returned.
    return 0;
  }
  //Iterates through waitTimesOfAllStudents to calculate sum and number of 0 wait times.
  for(int i = 0; i < waitTimesOfAllStudents->getLength(); ++i) {
    int value = waitTimesOfAllStudents->valueAt(i);
    if(value == 0) {
      //Should the wait time be a 0, increment numOfZeroes.
      ++numOfZeroes;
    } else {
      //Otherwise, add the wait time to the sum.
      sum += waitTimesOfAllStudents->valueAt(i);
    }
  }

  //If all the wait times are zero, return 0.
  if(numOfZeroes == waitTimesOfAllStudents->getLength()) {
    return 0;
  }
  //Otherwise, divide the sum by the number of waittimes minus the number of zero wait times.
  double mean = sum/(waitTimesOfAllStudents->getLength() - numOfZeroes);
  //Return the mean.
  return mean;
}

//Determine the mean of the window idle times.
double Simulation::meanWindowIdleTime() {
  //Declare a sum variable.
  double sum = 0;
  //Add all the window idle times up.
  for(int i = 0; i < numOfWindows; ++i) {
    sum += windows[i]->getIdleTime();
  }
  //Divide the sum by the num of windows to get the mean.
  double mean = sum/numOfWindows;
  //Return the mean.
  return mean;
}

//Determine the median wait time of the wait times.
int Simulation::medianStudentWaitTime() {
  //Sort all wait times from smallest to biggest, find the midpoint, at return the value at the midpoint.
  waitTimesOfAllStudents->sortSelf();
  int midpoint = waitTimesOfAllStudents->getLength()/2;
  return waitTimesOfAllStudents->valueAt(midpoint);
}

//Determine the maximum student waitTime.
int Simulation::maxStudentWaitTime() {
  //Initialize a max variable to hold the maximum wait time.
  int max = 0;
  //Iterate through waitTimesOfAllStudents, changing max each time the data being looked at is greater than/equal to max.
  for(int i = 0; i < waitTimesOfAllStudents->getLength(); ++i) {
    int valueAtI = waitTimesOfAllStudents->valueAt(i);
    if(valueAtI >= max) {
      max = valueAtI;
    }
  }
  //Return max.
  return max;
}

//Determine the maximum window idle time.
int Simulation::maxWindowIdleTime() {
  //Initialize a max variable to hold the maximum idleTime time.
  int max = 0;
  //Iterate through the windows array, changing max each time the idle time being looked at is greater than/equal to max.
  for(int i = 0; i < numOfWindows; ++i) {
    if(windows[i]->getIdleTime() >= max) {
      max = windows[i]->getIdleTime();
    }
  }
  //Return max.
  return max;
}

//Return the number of students who waited over ten minutes for a window.
int Simulation::studentWaitOverTenFinder() {
  //Initialize the student counter.
  int studentCounter = 0;
  //Iterate through waitTimesOfAllStudents, incrementing studentCounter whenever a wait time of more than 10 is found.
  for(int i = 0; i < waitTimesOfAllStudents->getLength(); ++i) {
    if(waitTimesOfAllStudents->valueAt(i) > 10) {
      ++studentCounter;
    }
  }
  //Return studentCounter
  return studentCounter;
}

//Return the number of windows idle for more than 5 minutes.
int Simulation::windowIdleTimeOverFiveFinder() {
  //Initialize the window counter.
  int windowCounter = 0;
  //Iterate through the windows array, incrementing windowCounter whenever a cumulative idle time of more than 5 is found.
  for(int i = 0; i < numOfWindows; ++i) {
    if(windows[i]->getIdleTime() > 5) {
      windowCounter++;
    }
  }
  //Return windowCounter
  return windowCounter;
}
