// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Utilities used by test cases.

#ifndef KATA_TEST_H
#define KATA_TEST_H

#include <Print.h>

#define CLASS_FUNCTION(class_name)                                         \
 public:                                                                   \
  class_name() { std::cout << #class_name "()" << std::endl; }             \
  class_name(class_name&) { std::cout << #class_name "(&)" << std::endl; } \
  class_name(class_name&&) noexcept {                                      \
    std::cout << #class_name "(&&)" << std::endl;                          \
  }                                                                        \
  ~class_name() { std::cout << "~" #class_name "()" << std::endl; }

#define CLASS(class_name)      \
  class class_name {           \
    CLASS_FUNCTION(class_name) \
  };

CLASS(A)
CLASS(B)
CLASS(C)

#define DELETE(p) \
  if (p) {        \
    delete p;     \
    p = nullptr;  \
  }

#endif  // KATA_TEST_H
