// Created by Jiaheng on 2021/5/12.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/container/var_type_dict.h"

struct A;
struct B;
struct W;

template <typename T>
auto linear_function(const T& tp) {
  auto a      = tp.template Get<A>();
  auto b      = tp.template Get<B>();
  auto weight = tp.template Get<W>();

  return a * weight + b * (1 - weight);
}

TEST(TestContainer, type_dict) {
  using namespace kata;

  EXPECT_EQ(
      linear_function(
          VarTypeDict<A, B, W>::Create().Set<A>(1.3).Set<B>(2.4).Set<W>(0.1)),
      2.29);
}

struct C;

template <typename T>
auto modify_pointer(const T& tp) {
  return ++(*tp.template Get<C>());  // pass as pointer
}

TEST(TestContainer, type_dict_reference) {
  using namespace kata;

  int c = 0;

  modify_pointer(VarTypeDict<C>::Create().Set<C>(&c));

  EXPECT_EQ(c, 1);
}
