// Created by Jiaheng on 2021/5/12.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

#include "kata/container/type_dict.h"

struct A;
struct B;
struct W;  // weight

template <typename T>
auto test_type_dict(const T& tp) {
  auto a      = tp.template Get<A>();
  auto b      = tp.template Get<B>();
  auto weight = tp.template Get<W>();

  return a * weight + b * (1 - weight);
}

TEST(TestContainer, type_dict) {
  using TParams = kata::TypeDict<A, B, W>;

  EXPECT_EQ(
      test_type_dict(TParams::Create().Set<A>(1.3).Set<B>(2.4).Set<W>(0.1)),
      2.29);
}

struct C;

template <typename T>
auto test_type_dict_influence_pointer(const T& tp) {
  return ++(*tp.template get<C>());  // pass as pointer
}

TEST(TestContainer, type_dict_reference) {
  using TParams = kata::TypeDict<C>;

  int c = 0;
  test_type_dict_influence_pointer(TParams::Create().set<C>(&c));

  EXPECT_EQ(c, 1);
}
