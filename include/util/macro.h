// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Macro defs for general use.

#ifndef DJA_MACRO_H_
#define DJA_MACRO_H_

#include <iostream>

// alwasys inline
#if defined _MSC_VER_
// win, visual studio
#define force_inline __forceinline
#elif defined __GNUC__
// gcc (Linux/Apple OS X)
#define force_inline __inline__ __attribute__((always_inline))
#else
#define force_inline
#endif

// output
#define print(x) std::cout << (x) << std::endl

#endif
