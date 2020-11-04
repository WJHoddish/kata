// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_TYPE_COUNT_H
#define KATA_TYPE_COUNT_H

namespace kata {
template <typename T, typename... Args>
struct type_count;

/**
 *
 * @tparam T
 * @tparam Head
 * @tparam Rest
 */
template <typename T, typename Head, typename... Rest>
struct type_count<T, Head, Rest...> {
  enum { value = type_count<T, Rest...>::value + 1 };
};

template <typename T>
struct type_count<T> {
  enum { value = 1 };
};

} // namespace kata

#endif // KATA_TYPE_COUNT_H
