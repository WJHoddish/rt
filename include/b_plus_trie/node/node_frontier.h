// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// B+ tree leaf node.

#ifndef BPT_NODE_LEAF_H
#define BPT_NODE_LEAF_H

#include "node.h"

namespace bpt {
struct NodeFrontier : public Node {
  NodeFrontier* prev_;
  NodeFrontier* next_;

  NodeFrontier()
      : prev_(nullptr)
      , next_(nullptr) {
    // set_leaf(status_);
  }

  ~NodeFrontier() {}
};

template <typename F>
force_inline constexpr auto router(Node* p, F&& f) {
  return is_leaf(p->status_) ? f(reinterpret_cast<NodeLeaf*>(p))
                             : f(reinterpret_cast<NodeIndex*>(p));
}

} // namespace bpt

#endif
