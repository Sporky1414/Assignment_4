/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 3
*/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


//Class used to take in and read an input file.
class FileIO {
  public:
    //Constructor/Destructor
    FileIO();
    FileIO(string tempInputFilePath);
    ~FileIO();

    //Methods to read data.
    string readNextLine();

    //Method to check on status of the input file.
    bool inputHasDataLeft();

    //Method to return the value of counter;
    int getLineNumber();

  private:
    //Gets the file path/name from the user for the input file.
    string getInputFilePathFromUser();

    //Strings containing the file path of the input file.
    string inputFilePath;

    //Object to take in data from a file.
    ifstream input;

    //Counts line number;
    int counter;
};
