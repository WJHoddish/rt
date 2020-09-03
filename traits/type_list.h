// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Store variable-length template arguments in a list.

#ifndef DJA_TYPE_LIST_H_
#define DJA_TYPE_LIST_H_

#include <cstddef>

namespace crrt {
template <typename...>
struct type_list;

template <>
struct type_list<> {};

template <typename Head, typename... Tail>
struct type_list<Head, Tail...> {
  using head = Head;

  using tail = type_list<Tail...>;
};

} // namespace crrt

#endif
