// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_SWITCH_CASE_H
#define KATA_SWITCH_CASE_H

#include <type_traits>

namespace kata {

//

template <std::size_t Idx, typename TCurrent, typename TNext = void>
struct case_ {
  using type = TCurrent;
  using next = TNext;
  enum { value = Idx };
};

//

template <std::size_t Idx, typename TCase>
struct switch_ {
  using next = typename TCase::next;
  using type = typename std::conditional_t<Idx == TCase::value,
                                           typename TCase::type,
                                           typename switch_<Idx, next>::type>;
};

template <std::size_t Idx>
struct switch_<Idx, void> {
  using type = void;
};

//

template <std::size_t Idx, typename T>
using switch_t = typename switch_<Idx, T>::type;

}  // namespace kata

#endif  // KATA_SWITCH_CASE_H
