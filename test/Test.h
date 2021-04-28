// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_TEST_H
#define KATA_TEST_H

#include <iostream>

#include "kata/noncopyable.h"

#define CLASS(class_name)                                             \
  struct class_name {                                                 \
    class_name() { std::cout << #class_name "()" << std::endl; }      \
    ~class_name() { std::cout << "~" #class_name "()" << std::endl; } \
  };

CLASS(A)
CLASS(B)
CLASS(C)

class D : public kata::Noncopyable {};

#endif  // KATA_TEST_H
