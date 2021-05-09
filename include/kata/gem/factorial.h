// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Factorial.

#ifndef KATA_FACTORIAL_H
#define KATA_FACTORIAL_H

namespace gem {

//

template <std::size_t N>
struct factorial {
  enum { value = N * factorial<N - 1>::value };
};

template <>
struct factorial<0> {
  enum { value = 1 };
};

}  // namespace gem

#endif  // KATA_FACTORIAL_H
