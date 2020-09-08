// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// B+ tree index node.

#ifndef BPT_NODE_INDEX_H
#define BPT_NODE_INDEX_H

#include "node.h"

namespace bpt {
struct NodeIndex : public Node {
  Node* child_[16];

  NodeIndex() {
    print("NodeIndex()");
  }

  ~NodeIndex() {
    print("~NodeIndex()");
  }
};
} // namespace bpt

#endif
