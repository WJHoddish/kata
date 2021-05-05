// Created by Jiaheng on 2021/5/4.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#include <Test.h>

#include <memory>

#include "kata/fill.h"

TEST(TestMoreTraits, tuple_index) {
  using namespace kata;

  auto producer = []() {
    char c = 'a';
    auto p = std::make_shared<int>(9);

    return std::tuple<char, std::shared_ptr<int>>(c, p);
  };

  auto consumer = [](char c, const std::shared_ptr<int>& p) { print(c, *p); };

  // extract arguments from tuple
  fill(consumer, producer());
}