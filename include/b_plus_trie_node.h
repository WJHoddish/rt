// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Node with multiple flag bits.

#ifndef BPT_NODE_H
#define BPT_NODE_H

#include "defs.h"
#include "type.h"

namespace bpt {
using Char = dja::Char;

using Size = dja::Size;

const uint32_t INSERT = (uint32_t)1 << 31;
const uint32_t DELETE = (uint32_t)1 << 30;
const uint32_t SPLIT  = (uint32_t)1 << 29;
const uint32_t LOCK   = (uint32_t)1 << 28;
const uint32_t ROOT   = (uint32_t)1 << 27;
const uint32_t LEAF   = (uint32_t)1 << 26;

// Using AND/OR operation to fix a particular bit.

#define set_insert(n) ((n) | bpt::INSERT)
#define set_delete(n) ((n) | bpt::DELETE)
#define set_split(n) ((n) | bpt::SPLIT)
#define set_lock(n) ((n) | bpt::LOCK)
#define set_root(n) ((n) | bpt::ROOT)
#define set_leaf(n) ((n) | bpt::LEAF)

#define unset_insert(n) ((n) & (~bpt::INSERT))
#define unset_delete(n) ((n) & (~bpt::DELETE))
#define unset_split(n) ((n) & (~bpt::SPLIT))
#define unset_lock(n) ((n) & (~bpt::LOCK))
#define unset_root(n) ((n) & (~bpt::ROOT))
#define unset_leaf(n) ((n) & (~bpt::LEAF))

struct Node {
  enum Type { INDEX = 0, LEAF };
};

} // namespace bpt

#endif