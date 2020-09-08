// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Base node with multiple flag bits.

#ifndef BPT_NODE_H
#define BPT_NODE_H

#include "defs.h"
#include "spread.h"
#include "status.h"

namespace bpt {
struct NodeIndex;

struct Node {
  uint32_t   status_;
  uint64_t   spread_;
  NodeIndex* parent_; // index node

  uint64_t keys_[15];

  Node()
      : status_(0)
      , spread_(0)
      , parent_(nullptr) {
    print("Node()");
  }

  ~Node() {
    print("~Node()");
  }
};

struct NodeLeaf;

template <typename F>
force_inline constexpr auto router(Node* p, F&& f) {
  if (is_leaf(p->status_)) {
    f(reinterpret_cast<NodeLeaf*>(p));
  } else {
    f(reinterpret_cast<NodeIndex*>(p));
  }
}

} // namespace bpt

#endif