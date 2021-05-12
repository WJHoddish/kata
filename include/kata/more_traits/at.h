// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_AT_H
#define KATA_AT_H

#include <kata/more_traits/type_list.h>

namespace kata {

//

template <std::size_t Idx, typename TContainer>
struct at;

template <std::size_t Idx, typename TCurrent, typename... TRemains>
struct at<Idx, type_list<TCurrent, TRemains...>> {
  using type = typename at<Idx - 1, type_list<TRemains...>>::type;
};

template <typename TCurrent, typename... TRemains>
struct at<0, type_list<TCurrent, TRemains...>> {
  using type = TCurrent;
};

//

template <std::size_t Idx, typename... Args>
using at_t = typename at<Idx, type_list<Args...>>::type;

}  // namespace kata

#endif  // KATA_AT_H
