#include "../gem/gem.h"
#include "../util/util.h"
#include <gtest/gtest.h>

TEST(test_math, boolean) {
  print("absolute value");
  print(gem::abs(0.618));
  print(gem::abs(-3.141));
  print(gem::abs(0));

  print("min/max");
  print(gem::min(6, 7.14285, 3.141, 4));
  print(gem::max(6, 7.14285, 3.141, 4));
}