// Created by Jiaheng on 2021/5/3.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#ifndef KATA_TUPLE_INDEX_H
#define KATA_TUPLE_INDEX_H

#include <tuple>

namespace kata {

//

template <std::size_t... Idxes>
struct tuple_index {
  ;
};

//

template <std::size_t Idx, typename T = tuple_index<>>
struct tuple_index_builder;

//

template <std::size_t Idx, std::size_t... Idxes>
struct tuple_index_builder<Idx, tuple_index<Idxes...>>
    : public tuple_index_builder<Idx - 1,
                                 tuple_index<Idxes..., sizeof...(Idxes)>> {
  ;
};

template <std::size_t... Idxes>
struct tuple_index_builder<0, tuple_index<Idxes...>> {
  using type = tuple_index<Idxes...>;
};

//

template <typename... Args>
using tuple_index_t = typename tuple_index_builder<sizeof...(Args)>::type;

}  // namespace kata

#endif  // KATA_TUPLE_INDEX_H
