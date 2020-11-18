/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/

#include "FileIO.h"
#include <iostream>
#include <fstream>

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
      if(isInputFileValid()) {
        break;
      } else {
        cout << "ERROR: File entered is not of correct format. Please try again." << endl;
        inputFilePath = getInputFilePathFromUser();
      }
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
      if(isInputFileValid()) {
        break;
      } else {
        cout << "ERROR: File entered is not of correct format. Please try again." << endl;
        inputFilePath = getInputFilePathFromUser();
      }
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
  input >> tempString;
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

//Check if file is in correct format
bool FileIO::isInputFileValid() {
  //Sets variable to remember beginning of file.
  streampos firstPos = input.tellg();
  //String to hold each line of the file.
  string tempString = "";
  //Assume the file is good unless a line comes back as invalid.
  bool fileIsValid = true;
  //Loops through entire file to check for format.
  while(inputHasDataLeft()) {
    //Reads line from file.
    tempString = readNextLine();
    //Check for empty line. If the line is empty, the file has an extra space that will make the program not work.
    //So the file is invalid and the method returns false.
    if(tempString.length() < 1) {
      return false;
    }
    //Checks to make sure each character is either a digit or a new line. If the character is neither, false is returned
    //Since this is in the wrong format then.
    for(int i = 0; i < tempString.length(); ++i) {
      if(!isdigit(tempString[i])) {
        if(tempString[i] != '\n') {
          return false;
        }
      }
    }
  }
  //Input file reader is reset to the beginning and true is returned, since the file passed the check.
  input.seekg(firstPos);
  return true;
}

int FileIO::getLineNumber() {
  return counter;
}
