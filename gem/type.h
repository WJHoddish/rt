// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Generalized Expression of Math (GEM).

#ifndef GEM_TYPE_H_
#define GEM_TYPE_H_

#include <limits>
#include <type_traits>

namespace gem {
using uint_t = unsigned int;

using llint_t = long long int;

template <class T>
using limit_t = std::numeric_limits<T>;

template <typename T>
using return_t = typename std::conditional<std::is_integral<T>::value, // ?
                                           double,                     // :
                                           T>::type;

template <typename... T>
using common_t = typename std::common_type<T...>::type;

// Obtains the common data type that all types in the list can be converted as.

template <typename... T>
using common_return_t = return_t<common_t<T...>>;

} // namespace gem

#endif