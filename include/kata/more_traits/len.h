// Created by Jiaheng on 2021/5/3.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//
// The sizeof type_list.

#ifndef KATA_LEN_H
#define KATA_LEN_H

#include "type_list.h"

namespace kata {

//

template <typename T = type_list<>>
struct len;

template <typename... Args>
struct len<type_list<Args...>> {
  enum { value = sizeof...(Args) };
};

}  // namespace kata

#endif  // KATA_LEN_H
