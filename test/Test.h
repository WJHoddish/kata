// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Utilities used by test cases.

#ifndef KATA_TEST_H
#define KATA_TEST_H

#include <gtest/gtest.h>

#define CLASS(class_name)                                                    \
  struct class_name {                                                        \
    class_name() { std::cout << #class_name "()" << std::endl; }             \
    class_name(class_name&) { std::cout << #class_name "(&)" << std::endl; } \
    class_name(class_name&&) noexcept {                                      \
      std::cout << #class_name "(&&)" << std::endl;                          \
    }                                                                        \
    ~class_name() { std::cout << "~" #class_name "()" << std::endl; }        \
  };

CLASS(A)
CLASS(B)
CLASS(C)

//

template <typename... Args>
void print(Args... args) {
  std::initializer_list<int>{(std::cout << args << '\t', 1)...};
  std::cout << '\n';
}

#endif  // KATA_TEST_H
