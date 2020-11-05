// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_BINARY_H
#define KATA_BINARY_H

namespace kata {
template <unsigned long N>
struct binary;

template <>
struct binary<1> {
  static unsigned const value = 1;
};

template <>
struct binary<0> {
  static unsigned const value = 0;
};

} // namespace kata

#endif // KATA_BINARY_H
