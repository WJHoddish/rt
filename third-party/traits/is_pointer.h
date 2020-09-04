// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Proof it is a pointer.

#ifndef DJA_IS_POINTER_H_
#define DJA_IS_POINTER_H_

namespace dja {
template <typename T>
struct is_pointer {
  static const bool value = false;
};

template <typename T>
struct is_pointer<T*> {
  static const bool value = true;
};

} // namespace dja

#endif
