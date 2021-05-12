// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Convert from binary to decimal integer.

#ifndef KATA_BINARY_H
#define KATA_BINARY_H

namespace gem {

//

template <std::size_t N>
struct binary {
  enum { value = binary<N / 10>::value << 1 | (N % 10) };
};

template <>
struct binary<0> {
  enum { value = 0 };
};

}  // namespace gem

#endif  // KATA_BINARY_H
