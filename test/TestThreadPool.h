// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include <atomic>
#include <thread>

#include "kata/thread/joining_thread.h"
#include "kata/thread/thread_pool.h"

static std::atomic<int> var;

static void func(std::size_t m, std::size_t n) {
  var += (int)n;

  std::this_thread::sleep_for(std::chrono::milliseconds(0));
}

TEST(TestThreadPool, kata_thread_pool) {
  {
    auto pool = kata::ThreadPool();
    for (int i = 0; i < 100; ++i) pool.enqueue(func, 0, i);
  }
  EXPECT_EQ(var -= 4950, 0);
  var = 0;
}
