// Test

#include "defs.h"
#include "utils/algorithm/sort.h"
#include <gtest/gtest.h>

using namespace dja;

TEST(test, sort) {
  // set an array of comparable elements
  std::vector<int> arg{1, 4, 2, 8, 5, 7};

  for (auto& ele : arg) std::cout << ele << ' ';
  print("");

  // select a sorting algorithm
  sort<SortShell>(arg);

  for (auto& ele : arg) std::cout << ele << ' ';
  print("");
}