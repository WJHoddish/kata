// Created by Jiaheng on 2021/4/30.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_MAX_H
#define KATA_MAX_H

#include <type_traits>

namespace gem {

//

template <typename T1, typename T2>
constexpr std::common_type_t<T1, T2> max(const T1 x, const T2 y) noexcept {
  return x > y ? x : y;
}

template <typename T, typename... Args>
constexpr std::common_type_t<T, Args...> max(const T x,
                                             const Args... y) noexcept {
  return x > max(y...) ? x : max(y...);
}

}  // namespace gem

#endif  // KATA_MAX_H
