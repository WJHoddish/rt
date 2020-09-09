// Test B+ Trie node.

#include "b_plus_trie/node/node.h"
#include <gtest/gtest.h>

using namespace dja::bpt;

TEST(test_b_plus_trie, node) {
  // make a node ()
  Node* leaf = new Node();

  for (uint8_t i = 0; i < Node::ORDER - 1; ++i) {
    std::cout << leaf->keys_[i] << ' ';
  }

  int a[10]{};

  for (uint8_t i = 0; i < 10; ++i) {
    std::cout << a[i] << ' ';
  }
}
