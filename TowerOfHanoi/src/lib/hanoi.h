#pragma once

#include <iostream>
#include <stack>
#include <string>

/*!
\brief   Rod is a class to maintains state about disk positions.
\details This class essentially is a wrapper around stack, to enforce a
capacity. and enforce inputs. Its use is to maintain state when we are moving
disks.
*/
class Rod {
  int mCapacity;
  std::string mName;
  std::stack<int> mDisks;

public:
  Rod(std::string name, int capacity);
  void push(int diskValue);
  int pop();
  bool isAtCapacity();
  bool isEmpty();
  friend class Hanoi;
};

/*!
\brief   Hanoi is a class that takes the action of moving disks between rods.
         It does this by encapsulates Rods for start, destination, and auxilary.
*/
class Hanoi {
  Rod start, dest, aux;
  int mRequiredMoves;
  int mDisks;
  bool mPrintState;
  void moveDisk(Rod &src, Rod &dest, std::ostream &out);
  void printState(std::ostream &out);

public:
  Hanoi(int disks, bool printState);
  void execute(std::ostream &out = std::cout);
};