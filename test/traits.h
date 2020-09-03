#include "../traits/traits.h"
#include "../util/util.h"
#include <gtest/gtest.h>

using namespace dja;

#define CLASS(x)                                                               \
  class x {                                                                    \
  public:                                                                      \
    x() {                                                                      \
      print(#x);                                                               \
    }                                                                          \
  };

CLASS(A)
CLASS(B)
CLASS(C)

TEST(test_traits, boolean) {
}

TEST(test_traits, type) {
  at<2, A, B, C>::type test_at; // C
}