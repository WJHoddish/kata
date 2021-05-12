// Created by Jiaheng on 2021/5/12.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/fill.h"

TEST(TestMoreTraits, tuple_index) {
  using namespace kata;

  auto producer = [](int m, int n) { return std::tuple<int, int>(m, n); };

  auto consumer = [](int m, int n) { return m + n; };

  EXPECT_EQ(fill(consumer, producer(5, 17)), 22);
}
