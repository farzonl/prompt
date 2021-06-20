#include "lib/hanoi.h"
#include <assert.h>
#include <iostream>
#include <vector>

void printUsage() {
  std::cout << "usage: ./TowerOfHanoi\n";
  std::cout << "       ./TowerOfHanoi <integer| # of disks>\n";
  std::cout << "       ./TowerOfHanoi <integer| # of disks> -print_state\n";
  std::cout << "       ./TowerOfHanoi -h\n";
}

int main(int argc, char *argv[]) {

  int disks = 0;
  bool printState = false;
  int printStateIndex = 0;
  if (argc > 3) {
    printUsage();
    return 0;
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-print_state") == 0) {
      printState = true;
      printStateIndex = i;
    }
    if (strcmp(argv[i], "-h") == 0) {
      printUsage();
      return 0;
    }
  }
  if ((argc == 1) || (printState && argc == 2)) {
    std::cout << "Please enter The number of disks: ";
    std::cin >> disks;
  } else if (argc == 2) {
    disks = atoi(argv[1]);
  } else {
    assert(argc == 3);
    int diskIndex = printStateIndex == 1 ? 2 : 1;
    disks = atoi(argv[diskIndex]);
  }

  if (argc <= 2 && printState == false) {
    char stateAns = 'n';
    std::cout << "Would you like to print state? (Y/N): ";
    std::cin >> stateAns;
    printState = (std::tolower(stateAns) == 'y');
  }

  Hanoi hanoi(disks, printState);
  hanoi.execute();
  return 0;
}