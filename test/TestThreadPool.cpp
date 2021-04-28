// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/thread_pool/joining_thread.h"
#include "kata/thread_pool/thread_pool.h"

TEST(TestThreadPool, ThreadPool) { std::cout << "hello, world" << std::endl; }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}