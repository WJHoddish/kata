// Created by Jiaheng on 2021/5/7.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/pattern/singleton.h"

namespace kata {

//

class D : public Singleton<D> {
 public:
  KATA_ENABLE_SINGLETON(D)
      : data(6) {}

  int data;
};

}  // namespace kata

TEST(TestPattern, singleton) {
  using namespace kata;

  EXPECT_EQ(D::get().data, 6);
}
