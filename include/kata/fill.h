// Created by Jiaheng on 2021/5/4.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//
// Feed a function on arguments extracted from given tuple.

#ifndef KATA_FILL_H
#define KATA_FILL_H

#include "more_traits/tuple_index.h"

namespace kata {

//

namespace _fill {

//

template <typename F, typename... Args, std::size_t... Idxes>
auto fill(F&& f, std::tuple<Args...>&& tp, tuple_index<Idxes...>) {
  return f(std::get<Idxes>(tp)...);
}

}  // namespace _fill

//

template <typename F, typename... Args>
auto fill(F&& f, std::tuple<Args...>&& tp) {
  return _fill::fill(f,
                     std::forward<typename std::tuple<Args...>>(tp),
                     tuple_index_t<Args...>());
}

}  // namespace kata

#endif  // KATA_FILL_H
