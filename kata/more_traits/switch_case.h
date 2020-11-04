// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_SWITCH_CASE_H
#define KATA_SWITCH_CASE_H

namespace kata {
/**
 *
 * @tparam tag
 * @tparam T
 * @tparam Next
 */
template <int tag, typename T, typename Next = void>
struct case_ {
  enum { tag_ = tag };

  using next = Next;

  using type = T;
};

/**
 *
 * @tparam tag
 * @tparam case_
 */
template <int tag, typename case_>
struct switch_ {
  using next = typename case_::next;

  using type = typename if_else<tag == case_::tag_,   //
                                typename case_::type, //
                                typename switch_<tag, next>::type>::type;
};

template <int tag>
struct switch_<tag, void> {
  using type = void;
};

} // namespace kata

#endif // KATA_SWITCH_CASE_H
