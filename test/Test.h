// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_TEST_H
#define KATA_TEST_H

#include <gtest/gtest.h>

#include "print.h"

#define CLASS(class_name)                                                     \
  struct class_name {                                                         \
    class_name() { std::cout << #class_name "()" << std::endl; }              \
    class_name(class_name &) { std::cout << #class_name "(&)" << std::endl; } \
    class_name(class_name &&) noexcept {                                      \
      std::cout << #class_name "(&&)" << std::endl;                           \
    }                                                                         \
    ~class_name() { std::cout << "~" #class_name "()" << std::endl; }         \
  };

CLASS(A)
CLASS(B)
CLASS(C)

#endif  // KATA_TEST_H
