// test my type_traits

#include "traits/traits.h"
#include "util/util.h"
#include <gtest/gtest.h>

using namespace dja;

#define CONSTRUCTOR(x)                                                         \
  x() {                                                                        \
    print(#x "()");                                                            \
  }

#define DESTRUCTOR(x)                                                          \
  ~x() {                                                                       \
    print("~" #x "()");                                                        \
  }

#define ENABLE_DESTRUCTOR

#define CLASS(x)                                                               \
  class x {                                                                    \
  public:                                                                      \
    CONSTRUCTOR(x)                                                             \
  };

CLASS(A)
CLASS(B)
CLASS(C)

TEST(test_traits, boolean) {
  std::cout << is_contain<A, B, C>() << std::endl;           // false
  std::cout << is_contain<int, A, B, C, int>() << std::endl; // true

  std::cout << is_pointer<A>::value << std::endl;  // false
  std::cout << is_pointer<A*>::value << std::endl; // true
}

TEST(test_traits, value) {
  std::cout << how_many<A, B, C>::value << std::endl; // 3
  std::cout << how_many<A, A>::value << std::endl;    // 2 (even if the same)

  max_int<7, 11, 33, 66>::type a;
  std::cout << a << std::endl;                             // 66
  std::cout << max_int<1, 9, 5, 7, 3>::value << std::endl; // 9

  std::cout << max_alignment<int, float, double>::value << std::endl; // 8
}

TEST(test_traits, type) {
  at<2, A, B, C>::type test_at; // C

  if_else<true, A, B>::type  test_if_else1; // A
  if_else<false, A, B>::type test_if_else2; // B

  switch_<2, case_<0, A, case_<2, C, case_<3, B>>>>::type test_switch_case; // C
}
