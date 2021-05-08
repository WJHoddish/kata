// Created by Jiaheng on 2021/5/7.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_TYPE_DICT_H
#define KATA_TYPE_DICT_H

#include <kata/more_traits/identity.h>

#include <memory>
#include <type_traits>

namespace kata {

//

namespace _type_dict {

//

template <std::size_t N,
          template <typename...>
          class TContainer,
          typename... TDummies>
struct default_tuple_type {
  struct Dummy {
    ;
  };

  using type =
      typename default_tuple_type<N - 1,
                                  TContainer,
                                  /**
                                   * Add a dummy type to the list, eventually
                                   * wrapped by a type container.
                                   */
                                  Dummy,
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
          /**
           * Remove current type if it's NOT target.
           */
          typename TCurrent,
          typename... TRemains>
struct type_2_id {
  enum { value = type_2_id<TTarget, N + 1, TRemains...>::value };
};

template <typename TTarget, std::size_t N, typename... TRemains>
struct type_2_id<TTarget,
                 N,
                 /**
                  * Successful match: target type & current type.
                  */
                 TTarget,
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
                                       /**
                                        * Archive current type.
                                        */
                                       TContainer<TArchives..., TCurrent>,
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
                          /**
                           * Put target type at a certain position.
                           */
                          TTarget,
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

}  // namespace _type_dict

//

template <typename... TKeys>
class TypeDict {
 public:
  static auto Create() {
    return _type_dict::default_tuple_type_t<sizeof...(TKeys), Values>{};
  }

 private:
  template <typename... Args>
  struct Values {
    std::shared_ptr<void> tuple_[sizeof...(Args)];

    //

    Values() = default;

    explicit Values(std::shared_ptr<void>(&&input)[sizeof...(Args)]) {
      for (std::size_t i = 0; i < sizeof...(Args); ++i)
        tuple_[i] = std::move(input[i]);
    }

    //

    template <typename TKey,
              /**
               * By default, value type is deducted by the passed-in variable.
               */
              typename TVal>
    auto set(TVal&& val) && {
      using namespace _type_dict;  // local namespace

      using TRaw                      = std::decay_t<TVal>;
      constexpr static std::size_t id = type_2_id<TKey, 0, TKeys...>::value;

      // replace the original void pointer
      tuple_[id] = std::shared_ptr<void>(
          new TRaw(std::forward<TVal>(val)),
          [](void* ptr) { delete static_cast<TRaw*>(ptr); });

      // reclaim tuple type after new value being registered
      return new_tuple_type_t<TRaw, id, Values<>, Args...>(std::move(tuple_));
    }

    template <typename TKey>
    auto& get() const {
      using namespace _type_dict;  // local namespace

      constexpr static std::size_t id = type_2_id<TKey, 0, TKeys...>::value;

      return *static_cast<id_2_type_t<id, Args...>*>(tuple_[id].get());
    }
  };
};

}  // namespace kata

#endif  // KATA_TYPE_DICT_H
