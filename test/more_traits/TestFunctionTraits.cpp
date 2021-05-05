// Created by Jiaheng on 2021/5/4.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#include <Test.h>

#include "kata/more_traits/function_traits.h"

class AA {
 public:
  void func(int i) const {}
};

static int func(char a, const short* b, float& c) {
  print(a, *b, c);

  return 0;
}

TEST(TestMoreTraits, function_traits) {
  using namespace kata;

  // return type
  EXPECT_EQ((std::is_same<typename function_traits<decltype(func)>::return_type,
                          int>::value),
            true);

  // argument type
  EXPECT_EQ((std::is_same<typename function_traits<decltype(func)>::arg_type<1>,
                          char>::value),
            true);
  EXPECT_EQ((std::is_same<typename function_traits<decltype(func)>::arg_type<2>,
                          const short*>::value),
            true);

  // cast as function pointer
  int (*cast)(char, const short*, float&) = func;

  EXPECT_EQ((std::is_same<typename function_traits<decltype(cast)>::arg_type<3>,
                          float&>::value),
            true);

  // member function
  EXPECT_EQ(
      (std::is_same<typename function_traits<decltype(&AA::func)>::arg_type<1>,
                    int>::value),
      true);

  // lambda
  auto f = [](char c, int i) { return 0; };

  EXPECT_EQ((std::is_same<typename function_traits<decltype(f)>::arg_type<1>,
                          char>::value),
            true);
  EXPECT_EQ((std::is_same<typename function_traits<decltype(f)>::arg_type<2>,
                          int>::value),
            true);
}
