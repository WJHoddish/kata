// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_AT_H
#define KATA_AT_H

namespace kata {

//

template <std::size_t Idx, typename... Args>
struct at;

//

template <std::size_t Idx, typename TCurrent, typename... TRemains>
struct at<Idx, TCurrent, TRemains...> {
  using type = typename at<Idx - 1, TRemains...>::type;
};

template <typename TCurrent, typename... TRemains>
struct at<0, TCurrent, TRemains...> {
  using type = TCurrent;
};

}  // namespace kata

#endif  // KATA_AT_H
