// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_IF_ELSE_H
#define KATA_IF_ELSE_H

namespace kata {
template <bool, typename T, typename F>
struct if_else {
  using type = T;
};

template <typename T, typename F>
struct if_else<false, T, F> {
  using type = F;
};
} // namespace kata

#endif // KATA_IF_ELSE_H
