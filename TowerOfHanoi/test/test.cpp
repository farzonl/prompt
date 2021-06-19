#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <unordered_map>

int solveHanoiRec(int disks, std::unordered_map<int, int> &memo) {
  if (disks < 2) {
    return disks;
  }
  if (disks == 2) {
    return 3;
  }
  if (memo.find(disks) != memo.end()) {
    return memo[disks];
  }
  int memoizeNextVal =
      1 + solveHanoiRec(disks - 1, memo) + solveHanoiRec(disks - 1, memo);
  memo[disks] = memoizeNextVal;
  return memoizeNextVal;
}

int solveHanoi(int disks) {
  std::unordered_map<int, int> memo;
  return solveHanoiRec(disks, memo);
}

TEST_CASE("Build Test") { REQUIRE(true); }