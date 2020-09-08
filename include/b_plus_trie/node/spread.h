// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Key(s) status.

#ifndef BPT_SPREAD_H
#define BPT_SPREAD_H

#define get_count(n) ((int)(n & 0xf))

#define get_index(n, i) ((int)((n >> (((i) + 1) * 4)) & 0xf))

#endif
