// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <atomic>
#include <thread>

static std::atomic<int> var;

static void func(std::size_t m, std::size_t n) {
  var += (int)n;

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}