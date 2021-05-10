// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_AND_OR_GATE_H
#define KATA_AND_OR_GATE_H

namespace kata {

//

template <typename T, bool X>
constexpr static bool and_ = false;

template <typename T>
constexpr static bool and_<T, true> = T::value;

//

template <typename T, bool X>
constexpr static bool or_ = true;

template <typename T>
constexpr static bool or_<T, false> = T::value;

}  // namespace kata

#endif  // KATA_AND_OR_GATE_H
