// Created by Jiaheng on 2021/5/11.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/controller/aop.h"

void func() { std::cout << "func" << std::endl; }

struct TimeElapsedAspect {
  static void Before() { std::cout << "Elapsed before" << std::endl; }
  static void Future() { std::cout << "Elapsed future" << std::endl; }
};

struct LoggingAspect {
  static void Before() { std::cout << "Logging before" << std::endl; }
  static void Future() { std::cout << "Logging future" << std::endl; }
};

TEST(TestController, aop) {
  using namespace kata;

  aop<LoggingAspect, TimeElapsedAspect>(&func);
}
