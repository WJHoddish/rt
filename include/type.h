// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Types.

#ifndef DJA_TYPE_H
#define DJA_TYPE_H

#include <cstddef>
#include <cstdlib>
#include <cstring>

namespace dja {
using Char = uint8_t;

using Size = std::size_t;

// A complete character array (head address & length), used as a string.

using Unit = std::pair<const Char*, Size>;

} // namespace dja

#endif
