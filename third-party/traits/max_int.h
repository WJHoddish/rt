// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Solve the largest integer.

#ifndef DJA_MAX_INT_H_
#define DJA_MAX_INT_H_

#include <cstddef>
#include <type_traits>

namespace dja {

template <int tag, int... args>
struct max_int;

template <int tag>
struct max_int<tag> : std::integral_constant<std::size_t, tag> {};

template <int arg1, int arg2, int... args>
struct max_int<arg1, arg2, args...>
    : std::integral_constant<int, arg1 >= arg2
                                      ? max_int<arg1, args...>::value
                                      : max_int<arg2, args...>::value> {};
} // namespace dja

#endif
