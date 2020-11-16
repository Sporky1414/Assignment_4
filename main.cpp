#include "Simulation.h"

using namespace std;

int main(int argc, char** argv) {
  string argument = "";
  if(argc >= 2) {
    argument = argv[1];
  }
  Simulation* simulation = new Simulation(argument);
  simulation->runSimulation();
  simulation->calculateAndReturnFinalData();
  delete simulation;
  return 0;
}
