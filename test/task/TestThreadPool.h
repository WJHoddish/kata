// Created by Jiaheng on 2021/5/5.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#include <atomic>
#include <thread>

static std::atomic<std::size_t> var = 0;

static void func(std::size_t m, std::size_t n) {
  var += n;

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}