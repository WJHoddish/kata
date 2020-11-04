// Copyright (c) 2020/11/3 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_FACTORIAL_H
#define KATA_FACTORIAL_H

namespace kata {
/**
 * Factorial of <N>.
 *
 * @tparam N
 */
template <int N>
struct factorial {
  enum { value = N * factorial<N - 1>::value };
};

template <>
struct factorial<0> {
  enum { value = 1 };
};

} // namespace kata

#endif
