// Copyright (c) 2020/11/4 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_ABS_H
#define KATA_ABS_H

namespace kata {
/**
 * Absolute value of <x>.
 *
 * @tparam T
 * @param x
 * @return
 */
template <typename T>
constexpr T abs(const T x) noexcept {
  return x < T(0)    ? -x   // abs(-1) = 1
         : x == T(0) ? T(0) // abs(0) = 0
                     : x;   // abs(1) = 1
}

} // namespace kata

#endif
