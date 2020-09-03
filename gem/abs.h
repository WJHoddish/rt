// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Solve the absolute value of x.

#ifndef GEM_ABS_H_
#define GEM_ABS_H_

namespace gem {

template <typename T>
constexpr T abs(const T& x) noexcept {
  return x == T(0) ? T(0) : x < T(0) ? -x : x;
}

} // namespace gem

#endif
