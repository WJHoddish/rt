// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// B+ tree & trie.

#ifndef BPT_H
#define BPT_H

#include "b_plus_trie_node.h"

namespace bpt {
template <typename T>
struct Trie {
  Trie() {
  }

  ~Trie() {
  }

  // CRUD

  template <typename... Args>
  Node* emplace(const Char* key, Size len, Args&&... args) {
    return nullptr;
  }

  template <typename... Args>
  Node* emplace(const char* key, /*~size*/ Args&&... args) {
    return emplace((Char*)key, strlen(key), std::forward<Args>(args)...);
  }

  T* find(const Char* key, Size len) const {
    return nullptr;
  }

  T* find(const char* key) const {
    return find((Char*)key, strlen(key));
  }

  // Data field

  Node*       root_;
  std::size_t size_;
};

} // namespace bpt

#endif