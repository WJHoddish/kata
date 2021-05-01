// Created by Jiaheng on 2021/4/30.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_IS_NAN_H
#define KATA_IS_NAN_H

namespace gem {

//

template <typename T>
constexpr bool is_nan(const T x) noexcept {
  return x != x;
}

}  // namespace gem

#endif  // KATA_IS_NAN_H
