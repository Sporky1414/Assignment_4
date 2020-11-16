/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 3
*/

#include "FileIO.h"

//Default constructor: takes in user input itself.
FileIO::FileIO() {
  //Gets preliminary file path from user.
  inputFilePath = getInputFilePathFromUser();

  //Loops until the inputFilePath is valid.
  while(true) {
    //Attempts to setup the file reader.
    input.open(inputFilePath);

    //If the file input reader works/sees the file exists, it will end the loop.
    if(!input.fail()) {
      break;
    } else {
      //The file path entered by the user is not a valid file path. User is alerted of this and has to try again.
      input.close();
      cout << "ERROR: Invalid file path. Please try again." << endl;
      inputFilePath = getInputFilePathFromUser();
    }
  }

  counter = 1;
}

//Constructor: takes in string, then user input if string invalid.
FileIO::FileIO(string tempInputFilePath) {
  //Sets inputFilePath to the string passed in through constructor
  inputFilePath = tempInputFilePath;

  //Loops until the inputFilePath is valid.
  while(true) {
    //Attempts to setup the file reader.
    input.open(inputFilePath);

    //If the file input reader works/sees the file exists, it will end the loop.
    if(!input.fail()) {
      break;
    } else {
      //The file path entered by the user is not a valid file path. User is alerted of this and has to try again.
      input.close();
      cout << "ERROR: Invalid file path. Please try again." << endl;
      inputFilePath = getInputFilePathFromUser();
    }
  }

  counter = 1;
}

//Destructor: Closes the input stream
FileIO::~FileIO() {
  if(input.is_open()) {
    input.close();
  }
}

//Reads the next line of the input file.
string FileIO::readNextLine() {
  string tempString = "";
  getline(input, tempString);
  ++counter;
  return tempString;
}

//Returns if there is more data in the file to read.
bool FileIO::inputHasDataLeft() {
  return !input.eof();
}

//Takes in the input file path from the user. It is not error checked in this method.
string FileIO::getInputFilePathFromUser() {
  cout << "Enter File Path for Input." << endl;
  string tempPath = "";
  cin >> tempPath;
  return tempPath;
}

int FileIO::getLineNumber() {
  return counter;
}
