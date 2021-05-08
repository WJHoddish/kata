// Created by Jiaheng on 2021/5/8.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Helper function template for casting from base to derived classes.

#ifndef KATA_STATIC_CAST_OR_DYNAMIC_CAST_H
#define KATA_STATIC_CAST_OR_DYNAMIC_CAST_H

#include <utility>

namespace kata {

//

template <typename R, typename S, typename = void>
struct static_cast_or_dynamic_cast_helper {
  constexpr R operator()(S& s) const {
    return dynamic_cast<R>(std::forward<S>(s));
  }
};

template <typename R, typename S>
struct static_cast_or_dynamic_cast_helper<
    R,
    S,
    decltype(static_cast<void>(static_cast<R>(std::declval<S>())))> {
  constexpr R operator()(S& s) const {
    return static_cast<R>(std::forward<S>(s));
  }
};

//

template <typename R, typename S>
constexpr R static_cast_or_dynamic_cast(S&& s) {
  return static_cast_or_dynamic_cast_helper<R, S>()(s);
}

}  // namespace kata

#endif  // KATA_STATIC_CAST_OR_DYNAMIC_CAST_H
