// Created by Jiaheng on 2021/5/4.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/pattern/singleton.h"

#define VALUE 100

class D : public kata::Singleton<D> {
 public:
  ENABLE_SINGLETON(D)
      : data(VALUE) {}

  int data;
};

TEST(TestPattern, singleton) {
  EXPECT_EQ(D::get().data, VALUE);

  // D obj;  // invalid
}

#undef VALUE

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}