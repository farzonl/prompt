#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "hanoi.h"
#include <doctest/doctest.h>
#include <sstream>

TEST_CASE("Test Capacity") {
  Rod rod("", 1);
  REQUIRE(rod.isAtCapacity() == false);
  rod.push(1);
  REQUIRE(rod.isAtCapacity());
}

TEST_CASE("Test empty") {
  Rod rod("", 1);
  rod.push(1);
  REQUIRE(rod.isEmpty() == false);
  rod.pop();
  REQUIRE(rod.isEmpty());
}

TEST_CASE("Test order") {
  Rod rod("", 3);
  rod.push(3);
  rod.push(2);
  rod.push(1);
  REQUIRE(rod.pop() == 1);
  REQUIRE(rod.pop() == 2);
  REQUIRE(rod.pop() == 3);
}

TEST_CASE("Test move set") {
  std::stringstream ssBaseline;
  int diskvalues[] = {1, 2, 1, 3, 1, 2, 1};
  std::string fromNames[] = {"start", "start", "dest", "start",
                             "aux",   "aux",   "start"};
  std::string toNames[] = {"dest",  "aux",  "aux", "dest",
                           "start", "dest", "dest"};
  int len = sizeof(diskvalues) / sizeof(diskvalues[0]);
  for (int i = 0; i < len; i++) {
    ssBaseline << "Move disk value " << diskvalues[i] << " From "
               << fromNames[i] << " to " << toNames[i] << std::endl;
  }
  std::stringstream ss;
  Hanoi hanoi(3, false);
  hanoi.execute(ss);
  REQUIRE(ssBaseline.str() == ss.str());
}