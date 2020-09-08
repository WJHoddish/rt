// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// B+ tree leaf node.

#ifndef BPT_NODE_LEAF_H
#define BPT_NODE_LEAF_H

#include "node_index.h"

namespace bpt {
struct NodeLeaf : public Node {
  NodeLeaf* prev_;
  NodeLeaf* next_;

  NodeLeaf()
      : prev_(nullptr)
      , next_(nullptr) {
    print("NodeLeaf()");

    set_leaf(status_);
  }

  ~NodeLeaf() {
    print("~NodeLeaf()");
  }
};

} // namespace bpt

#endif
