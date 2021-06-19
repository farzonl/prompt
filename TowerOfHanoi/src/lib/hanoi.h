#pragma once

#include <stack>
#include <string>

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

class Hanoi {
  Rod start, dest, aux;
  int mRequiredMoves;
  int mDisks;
  bool mPrintState;
  void moveDisk(Rod &src, Rod &dest);
  void printState();

public:
  Hanoi(int disks, bool printState);
  void execute();
};