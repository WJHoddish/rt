// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Sorting algorithms in a CRTP architecture.

#ifndef DJA_SORT_H
#define DJA_SORT_H

#include <type_traits>
#include <vector>

namespace dja {

// Customize a sortable index!

template <typename T>
using sort_t = std::vector<T>;

// The base class of SortMethod(s):
// Apply Curiously Recurring Template Pattern (CRTP):
// Inherit from a template base class;
// Derived class passes itself as template parameter.

template <template <typename X> typename SortMethod>
struct Sort {
  template <typename T>
  void operator()(sort_t<T>& arg) {
    static_cast<SortMethod<T>*>(this)->operator()(arg);
  }
};

template <template <typename X> typename SortMethod, typename T /*comparable*/>
auto sort(sort_t<T>& arg) ->
    typename std::enable_if<std::is_base_of<Sort<SortMethod>, // base class
                                            SortMethod<T>     // derived class
                                            >::value>::type {
  static SortMethod<T> sort_method;

  // use as a functor
  sort_method(arg);
}

#define SORT_METHOD(name)                                                      \
  template <typename T>                                                        \
  struct Sort##name : public Sort<Sort##name> {                                \
    void operator()(sort_t<T>& arg);                                           \
  };                                                                           \
                                                                               \
  template <typename T>                                                        \
  inline void Sort##name<T>::operator()(                                       \
      sort_t<T>& arg) /*add your sorting algorithms here*/

// Customize your sorting algorithms!

SORT_METHOD(Bubble) {
  auto len = arg.size();

  for (std::size_t i = 0; i < len - 1; ++i) {
    for (std::size_t j = 0; j < len - i - 1; ++j) {
      if (arg[j] > arg[j + 1]) {
        T temp     = arg[j];
        arg[j]     = arg[j + 1];
        arg[j + 1] = temp;
      }
    }
  }
}

SORT_METHOD(Insertion) {
  auto len = arg.size();

  for (std::size_t i = 1; i < len; ++i) {
    T    temp = arg[i];
    auto j    = i;
    for (; j > 0 && temp < arg[j - 1]; --j) arg[j] = arg[j - 1];
    arg[j] = temp;
  }
}

SORT_METHOD(Shell) {
  auto len = arg.size();

  for (std::size_t gap = len / 2; gap > 0; gap /= 2) {
    for (std::size_t i = gap; i < len; ++i) {
      T    temp = arg[i];
      auto j    = i;
      for (; j >= gap && temp < arg[j - gap]; j -= gap) arg[j] = arg[j - gap];
      arg[j] = temp;
    }
  }
}

} // namespace dja

#endif
