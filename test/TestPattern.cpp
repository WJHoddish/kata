// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/pattern/singleton.h"

class E : public kata::Singleton<E> {
  ENABLE_SINGLETON(E) {}
};

TEST(TestPattern, Singleton) { E::get(); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
