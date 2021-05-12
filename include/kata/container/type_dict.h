// Created by Jiaheng on 2021/5/7.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Variadic-Type Dictionary (VTD), a frequently-used function arguments wrapper.

#ifndef KATA_TYPE_DICT_H
#define KATA_TYPE_DICT_H

#include <kata/more_traits/identity.h>

#include <memory>
#include <type_traits>

namespace kata {

//

template <std::size_t N,
          template <typename...>
          class TContainer,
          typename... TDummies>
struct default_tuple_type {
  struct Dummy {
    ;
  };

  using type = typename default_tuple_type<N - 1,
                                           TContainer,
                                           Dummy,  // add N dummy types
                                           TDummies...>::type;
};

template <template <typename...> class TContainer, typename... TDummies>
struct default_tuple_type<0, TContainer, TDummies...> {
  using type = TContainer<TDummies...>;
};

//

template <std::size_t N, template <typename...> typename TContainer>
using default_tuple_type_t = typename default_tuple_type<N, TContainer>::type;

//

template <typename TTarget,
          std::size_t N,
          typename TCurrent,  // filter current type
          typename... TRemains>
struct type_2_id {
  enum { value = type_2_id<TTarget, N + 1, TRemains...>::value };
};

template <typename TTarget, std::size_t N, typename... TRemains>
struct type_2_id<TTarget,
                 N,
                 TTarget,  // current type is target type
                 TRemains...> {
  enum { value = N };
};

//

template <typename TTarget,
          std::size_t N,
          std::size_t M,
          typename TContainer,
          typename... TRemains>
struct new_tuple_type;

template <typename TTarget,
          std::size_t N,
          std::size_t M,
          template <typename...>
          typename TContainer,
          typename... TArchives,
          typename TCurrent,
          typename... TRemains>
struct new_tuple_type<TTarget,
                      N,
                      M,
                      TContainer<TArchives...>,
                      TCurrent,
                      TRemains...> {
  using type = typename new_tuple_type<TTarget,
                                       N,
                                       M + 1,
                                       TContainer<TArchives...,
                                                  TCurrent  // archive type
                                                  >,
                                       TRemains...>::type;
};

template <typename TTarget,
          std::size_t N,
          template <typename...>
          class TContainer,
          typename... TArchives,
          typename TCurrent,
          typename... TRemains>
struct new_tuple_type<TTarget,
                      N,
                      N,
                      TContainer<TArchives...>,
                      TCurrent,
                      TRemains...> {
  using type = TContainer<TArchives...,
                          TTarget,  // inject the new type
                          TRemains...>;
};

//

template <typename TTarget,
          std::size_t N,
          typename TContainer,
          typename... TRemains>
using new_tuple_type_t =
    typename new_tuple_type<TTarget, N, 0, TContainer, TRemains...>::type;

//

template <std::size_t N, typename... TRemains>
struct id_2_type;

template <std::size_t N, typename TCurrent, typename... TRemains>
struct id_2_type<N, TCurrent, TRemains...> {
  using type = typename std::conditional_t<(N == 0),
                                           identity<TCurrent>,
                                           id_2_type<N - 1, TRemains...>>::type;
};

//

template <std::size_t N, typename... TRemains>
using id_2_type_t = typename id_2_type<N, TRemains...>::type;

//

template <typename... TKeys>
class TypeDict {
  template <typename... Args>
  class Values {
    std::shared_ptr<void> m_tuple[sizeof...(Args)];

   public:
    Values() = default;

    explicit Values(std::shared_ptr<void>(&&input)[sizeof...(Args)]) {
      for (std::size_t i = 0; i < sizeof...(Args); ++i)
        m_tuple[i] = std::move(input[i]);
    }

    /**
     *
     * @tparam TKey
     * @tparam TVal
     * @tparam TRaw
     * @param val
     * @return
     */
    template <typename TKey, typename TVal, typename TRaw = std::decay_t<TVal>>
    auto Set(TVal&& val) && {
      // replace the original void pointer
      constexpr static std::size_t id = type_2_id<TKey, 0, TKeys...>::value;
      m_tuple[id]                     = std::shared_ptr<void>(
          new TRaw(std::forward<TVal>(val)),
          [](void* p) { delete static_cast<TRaw*>(p); }  // deleter
      );

      // reclaim tuple type after new value being registered
      return new_tuple_type_t<TRaw, id, Values<>, Args...>(std::move(m_tuple));
    }

    /**
     *
     * @tparam TKey
     * @return
     */
    template <typename TKey>
    auto& Get() const {
      constexpr static std::size_t id = type_2_id<TKey, 0, TKeys...>::value;
      return *static_cast<id_2_type_t<id, Args...>*>(m_tuple[id].get());
    }
  };

 public:
  static auto Create() {
    return default_tuple_type_t<sizeof...(TKeys), Values>{};
  }
};

}  // namespace kata

#endif  // KATA_TYPE_DICT_H
