/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/
#include "Simulation.h"

using namespace std;

//Main method to run the registration simulation
int main(int argc, char** argv) {
  //Takes in a command line argument with the file path of the file being used, should one be present.
  string argument = "";
  if(argc >= 2) {
    argument = argv[1];
  }
  //Creates a new simulation class from the argument file path.
  Simulation* simulation = new Simulation(argument);
  //Runs the simulation.
  simulation->runSimulation();
  //Calculates and displays the final results.
  simulation->calculateAndReturnFinalData();
  //Deletes the simulation object and returns 0 to end the program.
  delete simulation;
  return 0;
}
