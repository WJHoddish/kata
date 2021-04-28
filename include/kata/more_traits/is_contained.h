// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_IS_CONTAINED_H
#define KATA_IS_CONTAINED_H

namespace kata {

//

template <typename T, typename... Args>
struct is_contained;

//

template <typename T>
struct is_contained<T> : std::false_type {};

template <typename TTarget, typename TCurrent, typename... TRemains>
struct is_contained<TTarget, TCurrent, TRemains...>
    : std::conditional_t<std::is_same<TTarget, TCurrent>::value,
                         std::true_type,
                         is_contained<TTarget, TRemains...> > {
  //
};

}  // namespace kata

#endif  // KATA_IS_CONTAINED_H
