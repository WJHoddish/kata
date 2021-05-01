// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_IS_ALL_SAME_H
#define KATA_IS_ALL_SAME_H

#include <type_traits>

namespace kata {

//

template <typename T, typename... Args>
struct is_all_same;

//

template <typename T>
struct is_all_same<T> : std::true_type {
  ;
};

template <typename TTarget, typename TCurrent, typename... TRemains>
struct is_all_same<TTarget, TCurrent, TRemains...>
    : std::conditional_t<std::is_same<TTarget, TCurrent>::value,
                         is_all_same<TTarget, TRemains...>,
                         std::false_type> {
  ;
};

}  // namespace kata

#endif  // KATA_IS_ALL_SAME_H
