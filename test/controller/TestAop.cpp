// Created by Jiaheng on 2021/5/10.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <Test.h>

#include "kata/controller/aop.h"

struct TimeElapsedAspect {
  void Before(int i) { std::cout << "Elapse before" << std::endl; }

  void Future(int i) { std::cout << "Elapse future" << std::endl; }
};

struct LoggingAspect {
  void Before(int i) { std::cout << "Logging before" << std::endl; }

  void Future(int i) { std::cout << "Logging future" << std::endl; }
};

void foo(int a) { std::cout << "foo" << std::endl; }

TEST(TestController, aop) {
  using namespace kata;

  aop<LoggingAspect, TimeElapsedAspect>(&foo, 1);
}