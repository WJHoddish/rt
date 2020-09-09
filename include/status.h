// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Node status.

// Dirty bits: insert/delete/split.

#ifndef BPT_STATUS_H
#define BPT_STATUS_H

// Define flag bits.

#define bit_lock ((uint32_t)1 << 31)
#define bit_root ((uint32_t)1 << 30)
#define bit_leaf ((uint32_t)1 << 29)
#define bit_insert ((uint32_t)1 << 28)
#define bit_delete ((uint32_t)1 << 27)

// Set~

#define set_lock(n) ((n) |= bit_lock /*4-bytes*/)
#define set_root(n) ((n) |= bit_root)
#define set_leaf(n) ((n) |= bit_leaf)
#define set_insert(n) ((n) |= bit_insert)
#define set_delete(n) ((n) |= bit_delete)

// Clear~

#define clr_lock(n) ((n) & (~bit_lock))
#define clr_root(n) ((n) & (~bit_root))
#define clr_leaf(n) ((n) & (~bit_leaf))

// Judge~

#define is_lock(n) ((n) & (bit_lock))
#define is_root(n) ((n) & (bit_root))
#define is_leaf(n) ((n) & (bit_leaf))

#endif
