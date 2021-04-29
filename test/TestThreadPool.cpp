// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include "TestThreadPool.h"

#include <gtest/gtest.h>

#include "kata/thread/joining_thread.h"
#include "kata/thread/thread_pool.h"

using namespace kata;

TEST(TestThreadPool, ThreadPool) {
  {
    auto pool = ThreadPool();
    for (int i = 0; i < 100; ++i) pool.enqueue(func, 0, i);
  }

  EXPECT_EQ(var, 4950);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}