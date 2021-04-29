// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Understand input as a binary number and convert it to decimal integer.

#ifndef KATA_BINARY_H
#define KATA_BINARY_H

namespace kata {

//

template <std::size_t N>
struct binary {
  enum { value = binary<N / 10>::value << 1 | (N % 10) };
};

template <>
struct binary<0> {
  enum { value = 0 };
};

}  // namespace kata

#endif  // KATA_BINARY_H
