// Created by Jiaheng on 2021/5/3.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#ifndef KATA_SUM_H
#define KATA_SUM_H

namespace kata {

//

template <std::size_t Current, std::size_t... Remains>
struct sum {
  enum { value = Current + sum<Remains...>::value };
};

template <std::size_t Current>
struct sum<Current> {
  enum { value = Current };
};

}  // namespace kata

#endif  // KATA_SUM_H
