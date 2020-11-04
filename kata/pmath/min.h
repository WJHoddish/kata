// Copyright (c) 2020/11/4 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_MIN_H
#define KATA_MIN_H

#include <type_traits>

namespace kata {
template <typename... T>
using common_t = typename std::common_type<T...>::type;

/**
 * Choose the smaller one among two given numbers, maybe different in type.
 *
 * @tparam T1
 * @tparam T2
 * @param x
 * @param y
 * @return The common type that all params can be cast to.
 */
template <typename T1, typename T2>
constexpr common_t<T1, T2> min(const T1 x, const T2 y) noexcept {
  return x < y ? x : y;
}

template <typename T, typename... Ts>
constexpr common_t<T, Ts...> min(const T x, const Ts... y) noexcept {
  return x < min(y...) ? // choose the smaller one
             x
                       : //
             min(y...);
}

} // namespace kata

#endif