// Created by Jiaheng on 2021/5/12.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include <atomic>
#include <thread>

static std::atomic<std::size_t> var = 0;

static void func(std::size_t m, std::size_t n) {
  var += n;

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

#include "kata/task/thread_pool.h"

TEST(TestTask, thread_pool) {
  using namespace kata;

  {
    auto pool = ThreadPool();
    for (int i = 0; i < 100; ++i) pool.Enqueue(func, 0, i);
  }

  EXPECT_EQ(var -= 4950, 0);
}

#include "kata/task/repeat_pool.h"

TEST(TestTask, repeat_pool) {
  using namespace kata;

  auto pool = RepeatPool();
  pool.Run(func, 100);

  EXPECT_EQ(var -= 4950, 0);
}

TEST(TestTask, without_pool) {
  for (int i = 0; i < 100; ++i) func(0, i);

  EXPECT_EQ(var -= 4950, 0);
}