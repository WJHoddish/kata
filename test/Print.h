// Created by Jiaheng on 2021/5/10.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <gtest/gtest.h>

template <typename... Args>
void print(Args... args) {
  std::initializer_list<int>{(std::cout << args << '\t', 1)...};
  std::cout << '\n';
}
