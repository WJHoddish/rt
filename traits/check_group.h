// Copyright (C) summer 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Provide a boolean value if a type belongs to a type group.

#ifndef DJA_CHECK_GROUP_H_
#define DJA_CHECK_GROUP_H_

namespace dja {

// One security group, one primary data type.

#define CHECK_GROUP(group_name)                                                \
  template <typename T>                                                        \
  class check_##group_name;

#define CHECK_TRAIT(group_name, type_name)                                     \
  template <>                                                                  \
  class check_##group_name<type_name> {                                        \
  public:                                                                      \
    static constexpr bool value = true;                                        \
  };

#define CHECK(group_name, type_name) check_##group_name<type_name>::value

} // namespace dja

#endif
