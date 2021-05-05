// Created by Jiaheng on 2021/5/2.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#include "TestThreadPool.h"

#include <Test.h>

#include "kata/task/thread_pool.h"

TEST(TestTask, thread_pool) {
  using namespace kata;

  {
    auto pool = ThreadPool();
    for (int i = 0; i < 100; ++i) pool.enqueue(func, 0, i);
  }

  EXPECT_EQ(var, 4950);
}