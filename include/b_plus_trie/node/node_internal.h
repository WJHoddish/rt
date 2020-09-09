// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// B+ tree index node.

#ifndef DJA_BPT_NODE_INDEX_H
#define DJA_BPT_NODE_INDEX_H

#include "node.h"

namespace dja {
namespace bpt {
struct NodeIndex : public Node {
  Node* child_[ORDER];

  NodeIndex() {}

  ~NodeIndex() {}
};

} // namespace bpt

} // namespace dja

#endif
