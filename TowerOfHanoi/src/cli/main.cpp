#include "lib/hanoi.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

  int disks;
  bool printState = false;
  if (argc == 1) {
    std::cout << "Please enter The number of disks: ";
    std::cin >> disks;
  } else if (argc == 2) {
    disks = atoi(argv[1]);
  } else {
    return -1;
  }

  if (argc <= 2) {
    char stateAns = 'n';
    std::cout << "Would you like to print state? (Y/N): ";
    std::cin >> stateAns;
    printState = (std::tolower(stateAns) == 'y');
  }

  Hanoi hanoi(disks, printState);
  hanoi.execute();
  return 0;
}