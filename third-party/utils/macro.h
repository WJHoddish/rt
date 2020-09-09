// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Macro defs for general use.

#ifndef DJA_DEFS_H
#define DJA_DEFS_H

#include <iostream>

/**
 * @brief Standard output.
 *
 */
#define print(x) std::cout << (x) << std::endl

/**
 * @brief Make functions always inline.
 *
 */
#ifdef _MSC_VER_
#define force_inline __forceinline
#else
#ifdef __GNUC__
#define force_inline __inline__ __attribute__((always_inline))
#else
#define force_inline
#endif
#endif

/**
 * @brief Branch prediction.
 *
 */
#define yes_likely(x) (__builtin_expect(!!(x), 1))
#define not_likely(x) (__builtin_expect(!!(x), 0))

#endif
