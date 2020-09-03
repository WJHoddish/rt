// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// A pairwise function of getting the minimum value.

#ifndef GEM_MIN_H_
#define GEM_MIN_H_

#include "type.h"

namespace gem {

template <typename T1, typename T2>
constexpr common_t<T1, T2> min(const T1 x, const T2 y) noexcept {
  return x < y ? x : y;
}

template <typename T, typename... Ts>
constexpr common_t<T, Ts...> min(const T x, const Ts... y) noexcept {
  return x < min(y...) ? x : min(y...);
}

} // namespace gem

#endif