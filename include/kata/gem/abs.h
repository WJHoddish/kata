// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Calculate absolute value.

#ifndef KATA_ABS_H
#define KATA_ABS_H

namespace kata {

//

template <typename T>
constexpr T abs(const T x) noexcept {
  return x < T(0) ? -x : x == T(0) ? T(0) : x;
}

}  // namespace kata

#endif  // KATA_ABS_H
