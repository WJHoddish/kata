// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Compute absolute value.

#ifndef KATA_ABS_H
#define KATA_ABS_H

#include <type_traits>

namespace gem {

//

template <typename T>
constexpr T abs(const T x) noexcept {
  return x < T(0) ? -x : x == T(0) ? T(0) : x;
}

}  // namespace gem

#endif  // KATA_ABS_H
