#include "lstring.h"
#include "util/util.h"
#include <gtest/gtest.h>

using namespace dja;

TEST(test_string, init) {
  // init different types of cache line string

  LString little("hello");
  LString medium("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
  LString shared("abcdefghijklmnopqrstuvwxyz"
                 "abcdefghijklmnopqrstuvwxyz"
                 "abcdefghijklmnopqrstuvwxyz"
                 "abcdefghijklmnopqrstuvwxyz"
                 "abcdefghijklmnopqrstuvwxyz");

  print(little);
  print(medium);
  print(shared);
}

TEST(test_string, copy) {
  // copy constructor

  LString little("hello");
  LString medium("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
  LString shared("abcdefghijklmnopqrstuvwxyz"
                 "abcdefghijklmnopqrstuvwxyz"
                 "abcdefghijklmnopqrstuvwxyz"
                 "abcdefghijklmnopqrstuvwxyz"
                 "abcdefghijklmnopqrstuvwxyz");

  LString s1(little);
  LString s2(medium);
  LString s3(shared);

  print(s1);
  print(s2);
  print(s3);
}

TEST(test_string, copy_assignment) {
  // copy assignment

  LString little0("hello");
  LString medium0(
      "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz" /*52*/);
  LString shared0("abcdefghijklmnopqrstuvwxyz"
                  "abcdefghijklmnopqrstuvwxyz"
                  "abcdefghijklmnopqrstuvwxyz"
                  "abcdefghijklmnopqrstuvwxyz"
                  "abcdefghijklmnopqrstuvwxyz");

  // little -> medium
  little0 = medium0;
  print(little0);

  // medium -> medium
  LString medium1("This is a sentence with more than 30 chars");
  medium0 = medium1;
  print(medium0);

  LString medium2("abcdefghijklmnopqrstuvwxyz"
                  "abcdefghijklmnopqrstuvwxyz"
                  "abcdefghijklmnopqrstuvwxyz");
  medium0 = medium2;
  print(medium0);

  // shared
  LString shared1(
      "Now we are engaged in a great civil war, testing whether that nation, "
      "or any nation so conceived and so dedicated, can long endure. We are "
      "met on a great battle-field of that war. We have come to dedicate a "
      "portion of that field, as a final resting place for those who here gave "
      "their lives that nation might live. It is altogether fitting and proper "
      "that we should do this.");

  shared0 = shared1;
  print(shared0);
}

TEST(test_string, size) {
  print(sizeof(LString::Share));

  print(sizeof(LString::Arena));

  print(sizeof(LString));
}