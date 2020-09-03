// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Type "at" a pos "or" provide a default type if nothing found.

#ifndef DJA_AT_OR_H_
#define DJA_AT_OR_H_

#include "type_list.h"

namespace crrt {
template <std::size_t i, typename D, typename X /*type list*/>
struct at_or;

template <std::size_t i, typename D, typename Head, typename... Tail>
struct at_or<i, D, type_list<Head, Tail...>> {
  using type = typename at_or<i - 1, D, type_list<Tail...>>::type;
};

// Normal situation: successfully find a type at the correct position.

template <typename D, typename Head, typename... Tail>
struct at_or<0, D, type_list<Head, Tail...>> {
  using type = Head;
};

// Exception: run out of type list, use default type.

template <typename D, std::size_t i>
struct at_or<i, D, type_list<>> {
  using type = D;
};

} // namespace crrt

#endif
