// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_CHECK_GROUP_H
#define KATA_CHECK_GROUP_H

/**
 * e.g.
 *
 * CHECK_GROUP(random)
 */

#define CHECK_GROUP(group_name)                                                \
  template <typename T>                                                        \
  class check_##group_name;

/**
 * e.g.
 *
 * CHECK_REGISTER(random, kata::RandomInt)
 */

#define CHECK_REGISTER(group_name, type_name)                                  \
  template <>                                                                  \
  class check_##group_name<type_name> {                                        \
  public:                                                                      \
    static constexpr bool value = true;                                        \
  };

/**
 * e.g.
 *
 * CHECK(random, kata::RandomInt) === true
 */

#define CHECK(group_name, type_name) check_##group_name<type_name>::value

#endif // KATA_CHECK_GROUP_H
