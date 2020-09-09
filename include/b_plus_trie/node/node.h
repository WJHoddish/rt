// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// B+ tree base node.

#ifndef DJA_BPT_NODE_H
#define DJA_BPT_NODE_H

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace dja {
namespace bpt {
struct Node {
  static const uint8_t TREE_ORDER = 16;

  uint32_t status_;
  uint64_t spread_;
  Node*    parent_;
  uint64_t keys_[TREE_ORDER - 1];

  Node()
      : status_(0)
      , spread_(0)
      , parent_(nullptr)
      , keys_{} {}

protected:
  ~Node() {}

  static const uint32_t LOCK_BIT = (uint32_t)1 << 31;
  static const uint32_t ROOT_BIT = (uint32_t)1 << 30;
  static const uint32_t LEAF_BIT = (uint32_t)1 << 29;

  void lock() { this->status_ |= LOCK_BIT; }

  void setRoot() { this->status_ |= ROOT_BIT; }

  void setLeaf() { this->status_ |= LEAF_BIT; }
};

} // namespace bpt

} // namespace dja

#endif