// Created by Jiaheng on 2021/5/5.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#include <Test.h>

#include "kata/more_traits/at.h"

TEST(TestMoreTraits, at) {
  using namespace kata;

  EXPECT_EQ((std::is_same<at_t<0, A, B, C>, A>::value), true);
  EXPECT_EQ((std::is_same<at_t<2, A, B, C>, C>::value), true);
}

#include "kata/more_traits/len.h"

TEST(TestMoreTraits, len) {
  using namespace kata;

  EXPECT_EQ((len<type_list<char, short, int>>::value), 3);
}

#include "kata/more_traits/switch_case.h"

TEST(TestMoreTraits, switch_case) {
  using namespace kata;

  auto v1 = std::is_same<switch_t<2, case_<1, A, case_<2, B, case_<3, C>>>>,
                         B>::value,
       v2 = std::is_same<switch_t<3, case_<1, A, case_<2, B, case_<3, C>>>>,
                         C>::value;

  EXPECT_EQ(v1, true);
  EXPECT_EQ(v2, true);
}
