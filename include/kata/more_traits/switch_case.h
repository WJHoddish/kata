// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_SWITCH_CASE_H
#define KATA_SWITCH_CASE_H

#include <type_traits>

namespace kata {

//

template <std::size_t Tag, typename TCurrent, typename TNext = void>
struct case_ {
  enum { tag = Tag };
  using type = TCurrent;
  using next = TNext;
};

//

template <std::size_t Tag, typename TCase>
struct switch_ {
  using next = typename TCase::next;
  using type = typename std::conditional_t<Tag == TCase::tag,
                                           typename TCase::type,
                                           typename switch_<Tag, next>::type>;
};

template <std::size_t Tag>
struct switch_<Tag, void> {
  using type = void;
};

}  // namespace kata

#endif  // KATA_SWITCH_CASE_H
