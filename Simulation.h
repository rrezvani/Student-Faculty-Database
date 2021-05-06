#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "MenuManager.h"

using namespace std;

class Simulation {
  public:
    Simulation();
    ~Simulation();
    void simulate();
    void displayMenu();

    int userNum;

  private:
    MenuManager *menuManager; //menuManager reference
    string placeHolder;
};

#endif
