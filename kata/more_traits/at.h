// Copyright (c) 2020/11/3 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_AT_H
#define KATA_AT_H

namespace kata {
template <std::size_t i, typename... Args>
struct at;

/**
 * Solve the type at specified position.
 *
 * @tparam i
 * @tparam Head
 * @tparam Rest
 */
template <std::size_t i, typename Head, typename... Rest>
struct at<i, Head, Rest...> {
  using type = typename at<i - 1, Rest...>::type;
};

template <typename T, typename... Args>
struct at<0, T, Args...> {
  using type = T;
};

} // namespace kata

#endif
