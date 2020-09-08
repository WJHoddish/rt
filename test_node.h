// Test B+ Trie node.

#include "b_plus_trie/tree.h"
#include <gtest/gtest.h>

using namespace bpt;

TEST(test_b_plus_trie, node) {
  //
  Node* leaf = new NodeLeaf();

  print(leaf->status_);

  //
  router(leaf, [](auto x) { delete x; });
}
