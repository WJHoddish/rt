// Test components.

#include "b_plus_trie.h"
#include "utils/algorithm/sort.h"
#include <gtest/gtest.h>

TEST(test, sort) {
  using namespace dja;

  // set an array of comparable elements
  std::vector<int> arg{1, 4, 2, 8, 5, 7};

  for (auto& ele : arg) std::cout << ele << ' ';
  print("");

  // select a sorting algorithm
  sort<SortShell>(arg);

  for (auto& ele : arg) std::cout << ele << ' ';
  print("");
}

TEST(test, flag) {
  using namespace bpt;

  // set a B+ trie
  Trie<int> tree;

  // insert data

  // search

  // display
}
