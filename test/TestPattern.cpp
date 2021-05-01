// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "Test.h"
#include "kata/pattern/multiton.h"
#include "kata/pattern/singleton.h"

using namespace kata;

class E : public Singleton<E> {
  ENABLE_SINGLETON(E) {}
};

class F {
 public:
  F(int data)
      : data(data) {}

  int data;
};

TEST(TestPattern, singleton) { E::get(); }

TEST(TestPattern, multiton) {
  Multiton<F>::get("a", 1);
  Multiton<F>::get("a");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
