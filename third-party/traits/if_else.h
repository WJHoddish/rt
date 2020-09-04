// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Choose one between two given types.

#ifndef DJA_IF_ELSE_H_
#define DJA_IF_ELSE_H_

namespace dja {
template <bool, typename T, typename F>
struct if_else {
  using type = T;
};

template <typename T, typename F>
struct if_else<false, T, F> {
  using type = F; // if the statement is wrong, shows the second type
};

} // namespace dja

#endif
