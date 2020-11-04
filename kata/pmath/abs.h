// Copyright (c) 2020/11/4 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_ABS_H
#define KATA_ABS_H

namespace kata {
template <typename T>
constexpr T abs(const T& x) noexcept {
  return x == T(0) ? //
             T(0)
                   :    //
             x < T(0) ? //
                 -x
                      : //
                 x;
}

} // namespace kata

#endif
