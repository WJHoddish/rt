// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Solve the largest alignment.

#ifndef DJA_MAX_ALIGNMENT_H_
#define DJA_MAX_ALIGNMENT_H_

#include "max_int.h"

namespace dja {

template <typename... Args>
struct max_alignment
    : std::integral_constant<
          int, max_int<std::alignment_of<Args>::value...>::value> {};

} // namespace dja

#endif
