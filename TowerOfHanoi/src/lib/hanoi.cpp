#include "hanoi.h"
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <math.h>

// clang-format off
/*!
\brief   Initializes a Rod with a name and a capacity.
\param	 [in] name - the name of the rod.
\param	 [in] capacity - the maximum amount of disks allowed on this rod.
*/
// clang-format on
Rod::Rod(std::string name, int capacity) : mName(name), mCapacity(capacity) {}

// clang-format off
/*!
\brief   Checks if we have met the capacity limit.
\return	 the status of reaching the capacity limit.
*/
// clang-format on
bool Rod::isAtCapacity() { return mDisks.size() == mCapacity; }

bool Rod::isEmpty() { return mDisks.size() == 0; }

void Rod::push(int diskValue) {
  if (!isAtCapacity()) {
    mDisks.push(diskValue);
  }
}

// clang-format off
/*!
\brief   If the stack is not empty we will pop off the top disk.
\details This function will assert if the stack is empty.
\return	 The disk we are moving off the rod.
*/
// clang-format on
int Rod::pop() {
  assert(!isEmpty());
  int topDiskValue = mDisks.top();
  mDisks.pop();
  return topDiskValue;
  ;
}

// clang-format off
/*!
\brief   Initializes a Hanoi class with the size of the problem and whether we want to know state.
\details This constructor will also initalize the disks on the start rod and swap aux and dest rods on even # of disks.
\param	 [in] disks - the number of disks that we want to solve the puzzle for.
\param	 [in] printState - Determine if we want to print the state per move set.
*/
// clang-format on
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

// clang-format off
/*!
\brief   A function that moves disks from one rod to another.
\details Thi is where most of the work of this algorithm is. Depending on whats on the top of a rod will determine which rod we move to.
\param	 [in] rod1 - A rod we will want to move disks either too or off of depending on the top of the stack.
\param	 [in] rod2 - A second rod we will want to move disks either too or off of depending on the top of the stack.
*/
// clang-format on
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

// clang-format off
/*!
\brief   A function that executes the number of disk moves and reports the move set.
\details The Tower of Hanoi puzzle has a formulaic set of movement rules for fixed number of moves at 2^n -1. 
         The solution is knowing which move to do. wich is determined by taking the modulo of the number of  rods (3).
*/
// clang-format on
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

// clang-format off
/*!
\brief   Prints the state of the Rods in the hanoi problem.
\details This function makes the stack indexable. It achieves this by exposing 
         the protected collection field.
*/
// clang-format on
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

    std::cout << std::left << std::setw(start.mName.length() + 1) << startItem
              << std::setw(dest.mName.length() + 1) << destItem
              << std::setw(aux.mName.length() + 1) << auxItem << std::endl;
  }
}