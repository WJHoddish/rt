// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Line String: A string with an exact 32-bytes layout, makes classes which own
// it to be 64-bytes-long (fill an entire cache line).

#ifndef DJA_LSTRING_H
#define DJA_LSTRING_H

#include "traits/all_same.h"
#include "util/util.h"
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ostream>

namespace dja {
struct LString {
  // general data types, string category

  using Char = uint8_t;
  using Size = std::size_t;

  enum class Category { LITTLE = 0, MEDIUM, SHARED };

  // reference counting & core element: the arena

  struct Share {
    std::atomic<Size> cnt_;     /*8*/
    Char              data_[1]; /*8+1(7)=16*/

    static Share* create(const Char* str, Size len) {
      auto head =
          (Share*)malloc(sizeof(Share) /*already has an 1-byte data*/ + len);
      head->cnt_.store(1, std::memory_order_release);
      memcpy(head->data_, str, len);
      head->data_[len] = '\0';
      return head;
    }

    static Share* from(Char* p) {
      return static_cast<Share*>(static_cast<void*>(
          static_cast<char* /*1-byte type*/>(static_cast<void*>(p)) - // roll
          sizeof(cnt_)                                                // back
          ));
    }

    static unsigned int ref(Char* p) {
      return from(p)->cnt_.load(std::memory_order_acquire);
    }

    static void add(Char* p) {
      from(p)->cnt_.fetch_add(1, std::memory_order_acq_rel);
    }

    static void sub(Char* p) {
      auto head = from(p);
      auto temp = head->cnt_.fetch_sub(1, std::memory_order_acq_rel);
      if (temp == 1) {
        free(head);
        p[0] = '\0';
      }
    }
  };

  struct Arena {
    char  flag_;     /*1*/
    Char  data_[7];  /*1+7=8*/
    Char* ptr_;      /*8+8=16*/
    Size  size_;     /*16+8=24*/
    Size  capacity_; /*24+8=32 (whole data field)*/

    // how to modify (constructor, copy~ and destructor)

    Arena(const Char* str, Size len) {
      init(str, len);
    }

    Arena(const char* str) {
      init((Char*)str, strlen(str));
    }

    Arena(const Arena& src) {
      *this = src;
      switch (src.category()) {
      case Category::LITTLE: {
        break;
      }
      case Category::MEDIUM: {
        ptr_ = (Char*)malloc((src.size_ + 1) * sizeof(Char));
        memcpy(ptr_, src.ptr_, src.size_ + 1);
        break;
      }
      case Category::SHARED: {
        Share::add(ptr_); // reference count +1
        break;
      }
      }
    }

    ~Arena() {
      switch (category()) {
      case Category::LITTLE: {
        break;
      }
      case Category::MEDIUM: {
        free(ptr_);
        break;
      }
      case Category::SHARED: {
        Share::sub(ptr_); // reference count -1
        break;
      }
      }
    }

    // init

    force_inline void init(const Char* str, Size len) {
      if (len <= MAX_SIZE_LITTLE /*30*/) {
        initLittle(str, len);
      } else if (len <= MAX_SIZE_MEDIUM) {
        initMedium(str, len);
      } else {
        initShared(str, len);
      }
    }

    void initLittle(const Char* str, Size len) {
      flag_ = static_cast<char>(len); // make flag as the string length
      memcpy(data_, str, len);
      data_[len] = '\0';
    }

    void initMedium(const Char* str, Size len) {
      flag_ = 0x40;

      // dynamic memory allocation
      ptr_ = (Char*)malloc((len + 1) * sizeof(Char));
      memcpy(ptr_, str, len);
      ptr_[len] = '\0';
      size_     = len;
      capacity_ = len;
    }

    void initShared(const Char* str, Size len) {
      flag_ = 0x60;

      // create a shared unit, reference count = 1
      ptr_      = Share::create(str, len)->data_;
      size_     = len;
      capacity_ = len;
    }

    // bottlenecks

    force_inline Category category() const {
      if ((Size)flag_ <= MAX_SIZE_LITTLE) {
        return Category::LITTLE;
      } else if (flag_ == 0x40) {
        return Category::MEDIUM;
      } else if (flag_ == 0x60) {
        return Category::SHARED;
      }
      throw;
    }

    template <typename F1, typename F2, typename F3>
    force_inline static auto select(F1&& s, F2&& m, F3&& g, Category c) ->
        typename all_same<decltype(s()), decltype(m()), decltype(g())>::type {
      switch (c) {
      case Category::LITTLE:
        return s();
      case Category::MEDIUM:
        return m();
      case Category::SHARED:
        return g();
      }
      throw;
    }
  };

  constexpr static Size MAX_SIZE_LITTLE = sizeof(Arena) - 2;

  constexpr static Size MAX_SIZE_MEDIUM = 127;

  // make use of an arena in the string

  Arena arena_;

  LString(const Char* str, Size len)
      : arena_(str, len) {
  }

  LString(const char* str)
      : arena_(str) {
  }

  LString(const LString& src)
      : arena_(src.arena_) {
  }

  LString& operator=(const LString& src) {
    if (this != &src) {
      switch (arena_.category()) {
        // TODO(jiaheng): Firstly, check the category of own string.

      case Category::LITTLE: {
        arena_ = src.arena_; // copy the whole arena

        switch (src.arena_.category()) {
          // TODO(jiaheng): Secondly, check the category of opposite string.

        case Category::LITTLE: {
          break;
        }
        case Category::MEDIUM: {
          arena_.ptr_ = (Char*)malloc((src.arena_.size_ + 1) * sizeof(Char));
          memcpy(arena_.ptr_, src.arena_.ptr_, src.arena_.size_ + 1);
          break;
        }
        case Category::SHARED: {
          Share::add(arena_.ptr_);
          break;
        }
        }
        break;
      }
      case Category::MEDIUM: {
        switch (src.arena_.category()) {
        case Category::LITTLE: {
          free(arena_.ptr_);
          arena_ = src.arena_;
          break;
        }
        case Category::MEDIUM: {
          // check my capacity and opposite's size
          auto valid = arena_.capacity_;
          auto need  = src.arena_.size_;

          if (valid < need) {
            // existing space is not enough, need realloc
            free(arena_.ptr_);
            arena_.ptr_      = (Char*)malloc((need + 1) * sizeof(Char));
            arena_.capacity_ = need;
          }
          arena_.size_ = need;
          memcpy(arena_.ptr_, src.arena_.ptr_, need + 1);
          break;
        }
        case Category::SHARED: {
          free(arena_.ptr_);
          arena_ = src.arena_;
          Share::add(arena_.ptr_);
          break;
        }
        }
        break;
      }
      case Category::SHARED: {
        Share::sub(arena_.ptr_); // reference count -1
        arena_ = src.arena_;     // copy the whole arena

        switch (src.arena_.category()) {
        case Category::LITTLE: {
          break;
        }
        case Category::MEDIUM: {
          arena_.ptr_ = (Char*)malloc((src.arena_.size_ + 1) * sizeof(Char));
          memcpy(arena_.ptr_, src.arena_.ptr_, src.arena_.size_ + 1);
          break;
        }
        case Category::SHARED: {
          Share::add(arena_.ptr_);
          break;
        }
        }
        break;
      }
      }
    }
    return *this;
  }

  // std::string-like interfaces

  const Char* c_str() const {
    return arena_.category() == Category::LITTLE ? arena_.data_ : arena_.ptr_;
  }

  Size size() const {
    return arena_.category() == Category::LITTLE ? arena_.flag_ : arena_.size_;
  }

  Size capacity() const {
    return arena_.category() == Category::LITTLE ? MAX_SIZE_LITTLE
                                                 : arena_.capacity_;
  }

  // others

  void write(const char* fn) const {
    std::ofstream of;
    of.open(fn, std::ios_base::app);
    of << c_str() << '\n';
    of.close();
  }
};

inline std::ostream& operator<<(std::ostream& os, const LString& src) {
  os << src.c_str();
  return os;
}

} // namespace dja

#endif