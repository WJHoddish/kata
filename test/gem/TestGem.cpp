// Created by Jiaheng on 2021/5/11.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/gem/abs.h"

TEST(TestGem, abs) {
  EXPECT_EQ(gem::abs(0), 0.0);
  EXPECT_EQ(gem::abs(-0.618), 0.618);
  EXPECT_EQ(gem::abs(3.1415), 3.1415);
}

#include "kata/gem/binary.h"

TEST(TestGem, binary) {
  EXPECT_EQ(gem::binary<0>::value, 0);
  EXPECT_EQ(gem::binary<10>::value, 2);
  EXPECT_EQ(gem::binary<1101>::value, 13);
}

#include "kata/gem/factorial.h"

TEST(TestGem, factorial) {
  EXPECT_EQ(gem::factorial<0>::value, 1);
  EXPECT_EQ(gem::factorial<5>::value, 120);
}
