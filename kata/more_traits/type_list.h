// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_TYPE_LIST_H
#define KATA_TYPE_LIST_H

namespace kata {
template <typename...>
struct type_list;

/**
 *
 * @tparam Head
 * @tparam Rest
 */
template <typename Head, typename... Rest>
struct type_list<Head, Rest...> {
  using head = Head;
  using rest = type_list<Rest...>;
};

/**
 * Empty list.
 */
template <>
struct type_list<> {};

} // namespace kata

#endif // KATA_TYPE_LIST_H
