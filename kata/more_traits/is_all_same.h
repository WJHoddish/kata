// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_IS_ALL_SAME_H
#define KATA_IS_ALL_SAME_H

namespace kata {
template <typename T, typename... List>
struct is_all_same;

/**
 *
 * @tparam T
 */
template <typename T>
struct is_all_same<T> : std::true_type {
  using type = T;
};

template <typename T, typename Head, typename... Rest>
struct is_all_same<T, Head, Rest...>
    : std::conditional<!std::is_same<T, Head>::value, //
                       std::false_type,               //
                       is_all_same<T, Rest...>        //
                       >::type {};
} // namespace kata

#endif // KATA_IS_ALL_SAME_H
