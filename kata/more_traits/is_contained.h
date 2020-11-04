// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_IS_CONTAINED_H
#define KATA_IS_CONTAINED_H

#include <type_traits>

namespace kata {
template <typename T, typename... List>
struct is_contained;

/**
 *
 * @tparam T
 */
template <typename T>
struct is_contained<T> : std::false_type {};

template <typename T, typename Head, typename... Rest>
struct is_contained<T, Head, Rest...>
    : std::conditional<std::is_same<T, Head>::value, //
                       std::true_type,               //
                       is_contained<T, Rest...>      //
                       >::type {};

} // namespace kata

#endif // KATA_IS_CONTAINED_H
