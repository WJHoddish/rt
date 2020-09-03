// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Proof it is a void type.

#ifndef DJA_IS_VOID_H_
#define DJA_IS_VOID_H_

namespace dja {
template <typename T>
struct is_void {
  static const bool value = false;
};

template <>
struct is_void<void> {
  static const bool value = true;
};

} // namespace dja

#endif
