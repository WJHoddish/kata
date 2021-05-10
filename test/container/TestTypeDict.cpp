// Created by Jiaheng on 2021/5/7.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Unique typename is the tag of corresponding argument.

#include <Test.h>

#include "kata/container/type_dict.h"

struct A;
struct B;
struct C;
struct W;  // weight

using FParams = kata::TypeDict<A, B, W, C>;

template <typename T>
auto func(const T& tp) {
  auto a      = tp.template get<A>();
  auto b      = tp.template get<B>();
  auto weight = tp.template get<W>();

  (*(tp.template get<C>()))++;  // pass as pointer

  return a * weight + b * (1 - weight);
}

TEST(TestContainer, type_dict) {
  int i = 0;

  EXPECT_EQ(
      func(FParams::Create().set<A>(1.3).set<B>(2.4).set<W>(0.1).set<C>(&i)),
      2.29);

  EXPECT_EQ(i, 1);
}