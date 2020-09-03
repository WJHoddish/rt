// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Expand the use of "std::is_same<>".

#ifndef DJA_ALL_SAME_H
#define DJA_ALL_SAME_H

#include <type_traits>

namespace dja {
template <typename T, typename... List>
struct all_same;

template <typename T>
struct all_same<T> : std::true_type {
  using type = T;
};

template <typename T, typename Head, typename... Tail>
struct all_same<T, Head, Tail...>
    : std::conditional<!std::is_same<T, Head>::value, // ?
                       std::false_type,               // :
                       all_same<T, Tail...>>::type {};

} // namespace dja

#endif