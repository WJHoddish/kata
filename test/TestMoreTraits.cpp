// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "Test.h"
#include "kata/more_traits/and_or_gate.h"
#include "kata/more_traits/at.h"
#include "kata/more_traits/is_all_same.h"
#include "kata/more_traits/is_contained.h"
#include "kata/more_traits/switch_case.h"
#include "kata/more_traits/type_dict.h"

using namespace kata;

TEST(TestMoreTraits, and_or_gate) {}

TEST(TestMoreTraits, at) {}

TEST(TestMoreTraits, switch_case) {
  EXPECT_EQ(
      (std::is_same<
          typename switch_<2, case_<1, A, case_<2, B, case_<3, C>>>>::type,
          B>::value),
      true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
