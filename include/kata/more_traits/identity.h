// Created by Jiaheng on 2021/5/7.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_IDENTITY_H
#define KATA_IDENTITY_H

namespace kata {

//

template <typename T>
struct identity {
  using type = T;
};

//

template <typename T>
using identity_t = typename identity<T>::type;

}  // namespace kata

#endif  // KATA_IDENTITY_H
