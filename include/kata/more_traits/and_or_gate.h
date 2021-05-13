// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_AND_OR_GATE_H
#define KATA_AND_OR_GATE_H

namespace kata {

//

template <typename T, bool X>
constexpr static bool And = false;

template <typename T>
constexpr static bool And<T, true> = T::value;

//

template <typename T, bool X>
constexpr static bool Or = true;

template <typename T>
constexpr static bool Or<T, false> = T::value;

}  // namespace kata

#endif  // KATA_AND_OR_GATE_H
