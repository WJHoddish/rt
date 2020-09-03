// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// If the type is included by a given type list.

#ifndef DJA_IS_CONTAIN_H_
#define DJA_IS_CONTAIN_H_

#include <type_traits>

namespace dja {
template <typename T, typename... List>
struct is_contain;

template <typename T>
struct is_contain<T> : std::false_type {};

template <typename T, typename Head, typename... Tail>
struct is_contain<T, Head, Tail...>
    : std::conditional<std::is_same<T, Head>::value, // ?
                       std::true_type,               // :
                       is_contain<T, Tail...>>::type {};

} // namespace dja

#endif
