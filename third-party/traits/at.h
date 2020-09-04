// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Solve the type at any pos in the list.

#ifndef DJA_AT_H_
#define DJA_AT_H_

#include <cstddef>

namespace dja {

// Given a position and a list of types.

template <std::size_t i, typename... Args>
struct at;

template <std::size_t i, typename Head, typename... Tail>
struct at<i, Head, Tail...> {
  using type = typename at<i - 1, Tail...>::type;
};

template <typename T, typename... Args>
struct at<0, T, Args...> {
  using type = T;
};

} // namespace dja

#endif