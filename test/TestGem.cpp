// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/gem/abs.h"
#include "kata/gem/binary.h"
#include "kata/gem/factorial.h"
#include "kata/gem/floor.h"
#include "kata/gem/max.h"
#include "kata/gem/min.h"

TEST(TestGem, abs) {
  EXPECT_EQ(gem::abs(3.1415), 3.1415);
  EXPECT_EQ(gem::abs(-0.618), 0.618);
}

TEST(TestGem, binary) {
  EXPECT_EQ(gem::binary<0>::value, 0);
  EXPECT_EQ(gem::binary<10>::value, 2);
  EXPECT_EQ(gem::binary<1101>::value, 13);
}

TEST(TestGem, max_min) {
  EXPECT_EQ(gem::max(7.62, -1, 5.56, 2), 7.62);
  EXPECT_EQ(gem::min(7.62, -1, 5.56, 2), -1);
}

TEST(TestGem, factorial) {
  EXPECT_EQ(gem::factorial<3>::value, 6);
  EXPECT_EQ(gem::factorial<4>::value, 24);
}

TEST(TestGem, floor) {
  EXPECT_EQ(gem::floor(0.5), 0);
  EXPECT_EQ(gem::floor(-0.5), -1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
