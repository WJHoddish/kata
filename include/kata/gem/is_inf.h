// Created by Jiaheng on 2021/4/30.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_IS_INF_H
#define KATA_IS_INF_H

namespace gem {

//

template <typename T>
constexpr bool is_pos_inf(const T x) noexcept {
  return x == std::numeric_limits<T>::infinity();
}

template <typename T>
constexpr bool is_neg_inf(const T x) noexcept {
  return x == -std::numeric_limits<T>::infinity();
}

//

template <typename T>
constexpr bool is_inf(const T x) noexcept {
  return is_pos_inf(x) || is_neg_inf(x);
}

}  // namespace gem

#endif  // KATA_IS_INF_H
