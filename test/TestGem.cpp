// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/gem/abs.h"
#include "kata/gem/binary.h"
#include "kata/gem/extreme.h"
#include "kata/gem/factorial.h"

using namespace kata;

TEST(TestGem, abs) { EXPECT_EQ(kata::abs(-3.141), 3.141); }

TEST(TestGem, binary) { EXPECT_EQ(binary<1101>::value, 13); }

TEST(TestGem, extreme) {
  EXPECT_EQ(max(3, -1, 5.56, 2), 5.56);
  EXPECT_EQ(min(3, -1, 5.56, 2), -1);
}

TEST(TestGem, factorial) { EXPECT_EQ(factorial<4>::value, 24); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
