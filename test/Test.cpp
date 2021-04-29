// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include "Test.h"

#include <gtest/gtest.h>

TEST(Test, noncopyable) {
  D a;
  // D b(a);
}

TEST(Test, args) {
  EXPECT_EQ(ARGS(), 0);

  EXPECT_EQ(ARGS(char,
                 short,
                 int,
                 float,
                 double,
                 long,
                 unsigned int,
                 unsigned long long),
            8);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
