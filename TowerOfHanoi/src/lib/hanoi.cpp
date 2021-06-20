#include "hanoi.h"
#include <assert.h>
#include <iostream>
#include <math.h>

Rod::Rod(std::string name, int capacity) : mName(name), mCapacity(capacity) {}

bool Rod::isAtCapacity() { return mDisks.size() == mCapacity; }

bool Rod::isEmpty() { return mDisks.size() == 0; }

void Rod::push(int diskValue) {
  if (!isAtCapacity()) {
    mDisks.push(diskValue);
  }
}

int Rod::pop() {
  assert(!isEmpty());
  int topDiskValue = mDisks.top();
  mDisks.pop();
  return topDiskValue;
  ;
}

Hanoi::Hanoi(int disks, bool printState)
    : start("start", disks), dest("dest", disks), aux("aux", disks),
      mDisks(disks), mPrintState(printState) {
  mRequiredMoves = static_cast<int>(pow(2, disks) - 1);

  if (disks % 2 == 0) {
    std::string tempName = dest.mName;
    dest.mName = aux.mName;
    aux.mName = tempName;
  }

  for (int i = disks; i > 0; i--) {
    start.push(i);
  }
}

void Hanoi::moveDisk(Rod &rod1, Rod &rod2) {
  int diskValue = 0;
  std::string srcName = "";
  std::string destName = "";
  if (rod1.isEmpty() && rod2.isEmpty()) {
    // NOTE: This case should never hit
    // defining it to make the else condition
    // clear.
    assert(false);
    return;
  } else if (rod1.isEmpty() && !rod2.isEmpty()) {
    diskValue = rod2.pop();
    srcName = rod2.mName;
    destName = rod1.mName;
    rod1.push(diskValue);
  } else if (rod2.isEmpty() && !rod1.isEmpty()) {
    diskValue = rod1.pop();
    srcName = rod1.mName;
    destName = rod2.mName;
    rod2.push(diskValue);
  } else {
    int rod1Top = rod1.pop();
    int rod2Top = rod2.pop();
    if (rod1Top > rod2Top) {
      diskValue = rod2Top;
      srcName = rod2.mName;
      destName = rod1.mName;
      rod1.push(rod1Top);
      rod1.push(rod2Top);
    } else {
      diskValue = rod1Top;
      srcName = rod1.mName;
      destName = rod2.mName;
      rod2.push(rod2Top);
      rod2.push(rod1Top);
    }
  }
  std::cout << "Move disk value " << diskValue << " From " << srcName << " to "
            << destName << std::endl;
}

void Hanoi::execute() {
  for (int i = 1; i <= mRequiredMoves; i++) {
    printState();
    int rodChosen = i % 3;
    switch (rodChosen) {
    case 0:
      moveDisk(aux, dest);
      break;
    case 1:
      moveDisk(start, dest);
      break;
    case 2:
      moveDisk(start, aux);
      break;
    }
  }
  printState();
}
void Hanoi::printState() {
  if (!mPrintState) {
    return;
  }
  struct IndexableStack : public std::stack<int> {
    static int item(size_t const i, stack<int> const &s) {
      if (i < s.size()) {
        return (s.*&IndexableStack::c)[i];
      }
      return 0;
    }
  };

  std::cout << start.mName << " " << dest.mName << " " << aux.mName
            << std::endl;
  for (int i = mDisks - 1; i >= 0; i--) {
    int startItem = IndexableStack::item(i, start.mDisks);
    int destItem = IndexableStack::item(i, dest.mDisks);
    int auxItem = IndexableStack::item(i, aux.mDisks);

    std::cout << startItem << " " << destItem << " " << auxItem << std::endl;
  }
}