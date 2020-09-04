// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// A pairwise function of getting the maximum value.

#ifndef GEM_MAX_H_
#define GEM_MAX_H_

#include "type.h"

namespace gem {

template <typename T1, typename T2>
constexpr common_t<T1, T2> max(const T1 x, const T2 y) noexcept {
  return x > y ? x : y;
}

template <typename T, typename... Ts>
constexpr common_t<T, Ts...> max(const T x, const Ts... y) noexcept {
  return x > max(y...) ? x : max(y...);
}

} // namespace gem

#endif