// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Define member data according to other compile-time quantities.

#ifndef DJA_switch__case__H_
#define DJA_switch__case__H_

#include "if_else.h"

namespace dja {

// static case

struct case_null {};

template <int tag, typename T, typename Next = case_null>
struct case_ {
  enum { tag_ = tag };

  using next = Next;

  using type = T;
};

// static switch

const int switch_default = -1;

template <int tag, typename case_>
struct switch_ {
  enum { tag_ = case_::tag_, found_ = (tag_ == tag || tag_ == switch_default) };

  using next = typename case_::next;

  using type = typename if_else<found_,                           // true/false
                                typename case_::type,             // option.1
                                typename switch_<tag, next>::type // option.2
                                >::type;
};

template <int tag>
struct switch_<tag, case_null> {
  using type = case_null;
};

} // namespace dja

#endif
