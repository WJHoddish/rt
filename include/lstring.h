// Copyright (C) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Cache-Line String: A string with an exact 32-bytes layout, makes classes
// which own it to be 64-bytes-long (fill an entire cache line).

#ifndef DJA_LSTRING_H
#define DJA_LSTRING_H

#include "defs.h"
#include "traits/all_same.h"
#include "type.h"
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ostream>

namespace dja {
struct LString {
  enum class Category { LITTLE = 0, MEDIUM, SHARED };

  // Reference Counting Module (RCM):
  // Use an anchor pointer to navigate the place in which the count is stored.
  // The count number is ensured thread-safety.

  struct Share {
    std::atomic<Size> cnt_;     /*8*/
    Char              data_[1]; /*8+1(7)=16*/

    static Share* create(const Char* str, Size len) {
      auto head =
          (Share*)malloc(sizeof(Share) /*already has an 1-byte pad*/ + len);
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

  // Data Arena:
  // The layout is exact 32-bytes-long (in x64 machines).

  struct Arena {
    char  flag_;     /*1*/
    Char  data_[7];  /*1+7=8*/
    Char* ptr_;      /*8+8=16*/
    Size  size_;     /*16+8=24*/
    Size  capacity_; /*24+8=32 (whole data field)*/

    Arena(const char* str) {
      init((Char*)str, strlen(str));
    }

    Arena(const Char* str, Size len) {
      init(str, len);
    }

    Arena(const Arena& src) {
      *this = src; // copy the whole arena
      switch (src.category()) {
      case Category::LITTLE: {
        break;
      }
      case Category::MEDIUM: {
        ptr_ = (Char*)malloc(sizeof(Char) * (src.size_ + 1));
        memcpy(ptr_ /*ds*/, src.ptr_ /*sc*/, src.size_ + 1);
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
        break; // on-stack sso
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

    force_inline void init(const Char* str, Size len) {
      if (len <= MAX_SIZE_LITTLE /*30*/) {
        initLittle(str, len);
      } else if (len <= MAX_SIZE_MEDIUM) {
        initMedium(str, len);
      } else {
        initShared(str, len);
      }
    }

    force_inline void initLittle(const Char* str, Size len) {
      flag_ = static_cast<char>(len); // make flag as the string length
      memcpy(data_, str, len);
      data_[len] = '\0';
    }

    void initMedium(const Char* str, Size len) {
      flag_ = 0x40;

      // dynamic memory allocation
      ptr_ = (Char*)malloc(sizeof(Char) * (len + 1));
      memcpy(ptr_, str, len);
      ptr_[len] = '\0';
      size_     = len;
      capacity_ = len;
    }

    void initShared(const Char* str, Size len) {
      flag_ = 0x60;

      // create a shared unit
      ptr_      = Share::create(str, len)->data_;
      size_     = len;
      capacity_ = len;
    }

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
    }
  };

  constexpr static Size MAX_SIZE_LITTLE = sizeof(Arena) - 1 /*flag*/ - 1 /*\0*/;

  constexpr static Size MAX_SIZE_MEDIUM = 127;

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
        // Step.1: Check the own category.

        // Step.2: Check the opposite string (source).

      case Category::LITTLE: {
        arena_ = src.arena_; // copy the whole arena

        switch (src.arena_.category()) {
        case Category::LITTLE: {
          break;
        }
        case Category::MEDIUM: {
          arena_.ptr_ = (Char*)malloc(sizeof(Char) * (src.arena_.size_ + 1));
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
          // check the valid space (capacity) and needed size (opposite's size)
          auto need = src.arena_.size_;

          // realloc (existing space is not enough)
          if (arena_.capacity_ < need) {
            free(arena_.ptr_);
            arena_.ptr_      = (Char*)malloc(sizeof(Char) * (need + 1));
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
        arena_ = src.arena_;

        switch (src.arena_.category()) {
        case Category::LITTLE: {
          break;
        }
        case Category::MEDIUM: {
          arena_.ptr_ = (Char*)malloc(sizeof(Char) * (src.arena_.size_ + 1));
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

  const Char* c_str() const {
    return arena_.category() == Category::LITTLE ? arena_.data_ : arena_.ptr_;
  }

  std::size_t size() const {
    return arena_.category() == Category::LITTLE ? arena_.flag_ : arena_.size_;
  }

  std::size_t capacity() const {
    return arena_.category() == Category::LITTLE ? MAX_SIZE_LITTLE
                                                 : arena_.capacity_;
  }

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
