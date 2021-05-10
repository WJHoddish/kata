// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_TYPE_LIST_H
#define KATA_TYPE_LIST_H

namespace kata {

//

template <typename...>
struct type_list;

template <typename TCurrent, typename... TRemains>
struct type_list<TCurrent, TRemains...> {
  using type = TCurrent;
  using next = type_list<TRemains...>;
};

template <>
struct type_list<> {
  ;
};

}  // namespace kata

#endif  // KATA_TYPE_LIST_H
