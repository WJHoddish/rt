// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Count alive objects of a derived class in a CRTP hierarchy.

#ifndef DJA_OBJECT_COUNTER_H
#define DJA_OBJECT_COUNTER_H

#include <cstddef>

namespace dja {
template <typename T>
class ObjectCounter {
public:
  static std::size_t alive() {
    return ObjectCounter<T>::object_cnt_;
  }

protected:
  ObjectCounter() {
    ++ObjectCounter<T>::object_cnt_;
  }

  ObjectCounter(const ObjectCounter<T>&) {
    ++ObjectCounter<T>::object_cnt_;
  }

  ~ObjectCounter() {
    --ObjectCounter<T>::object_cnt_;
  }

  static std::size_t object_cnt_;
};

template <typename T>
std::size_t ObjectCounter<T>::object_cnt_ = 0;

} // namespace dja

#endif
