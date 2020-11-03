// Copyright (c) 2020/11/3 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_FACTORIAL_H
#define KATA_FACTORIAL_H

#include <cstddef>

namespace kata {
/**
 * Indicate the factorial by <value>.
 *
 * @tparam N
 */
template <std::size_t N>
struct factorial {
  enum { value = N * factorial<N - 1>::value };
};

/**
 * The end of recursion.
 */
template <>
struct factorial<0> {
  enum { value = 1 };
};

} // namespace kata

#endif
