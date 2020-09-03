// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Check type at any pos in the list.

#ifndef DJA_AT_H_
#define DJA_AT_H_

#include <cstddef>

namespace dja {
template <std::size_t idx, typename... Args>
struct at;

template <std::size_t idx, typename Head, typename... Tail>
struct at<idx, Head, Tail...> {
  using type = typename at<idx - 1, Tail...>::type;
};

template <typename T, typename... Args>
struct at<0, T, Args...> {
  using type = T;
};

} // namespace dja

#endif