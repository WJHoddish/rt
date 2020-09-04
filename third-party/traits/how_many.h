// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Number of types in the list.

#ifndef DJA_HOW_MANY_H_
#define DJA_HOW_MANY_H_

namespace dja {
template <typename T, typename... Args>
struct how_many;

template <typename T, typename Head, typename... Tail>
struct how_many<T, Head, Tail...> {
  enum { value = how_many<T, Tail...>::value + 1 };
};

// It takes at least one type in the list.

template <typename T>
struct how_many<T> {
  enum { value = 1 };
};

} // namespace dja

#endif
