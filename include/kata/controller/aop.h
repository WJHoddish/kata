// Created by Jiaheng on 2021/5/10.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Aspect-Oriented Programming (AOP), the programming paradigm.

#ifndef KATA_AOP_H
#define KATA_AOP_H

#include <kata/container/type_dict.h>
#include <kata/noncopyable.h>

#define KATA_AOP_MEMBER(member)                                          \
  template <typename T, typename... Args>                                \
  class has_member_##member {                                            \
    template <typename U>                                                \
    static auto Check(int)                                               \
        -> decltype(std::declval<U>().member(std::declval<Args>()...),   \
                    std::true_type());                                   \
    template <typename U>                                                \
    static std::false_type Check(...);                                   \
                                                                         \
   public:                                                               \
    enum {                                                               \
      value = std::is_same<decltype(Check<T>(0)), std::true_type>::value \
    };                                                                   \
  };

KATA_AOP_MEMBER(Before)
KATA_AOP_MEMBER(Future)

//

#define KATA_AOP_BOTH(x)                                   \
  std::enable_if_t<has_member_Before<x, Args...>::value && \
                   has_member_Future<x, Args...>::value>  // SFINAE

#define KATA_AOP_ONLY_BEFORE(x)                            \
  std::enable_if_t<has_member_Before<x, Args...>::value && \
                   !has_member_Future<x, Args...>::value>

#define KATA_AOP_ONLY_FUTURE(x)                             \
  std::enable_if_t<!has_member_Before<x, Args...>::value && \
                   has_member_Future<x, Args...>::value>

//

namespace kata {

//

template <typename F, typename... Args>
class Aop : public Noncopyable {
  F m_func;  ///< kernel function

 public:
  explicit Aop(F&& func)
      : m_func(std::forward<F>(func)) {
    ;
  }

  //

  template <typename TCurrent, typename... TRemains>
  auto Invoke(Args&&... args, TCurrent&& current, TRemains&&... remains)
      -> KATA_AOP_BOTH(TCurrent) {
    current.Before(std::forward<Args>(args)...);
    Invoke(std::forward<Args>(args)..., std::forward<TRemains>(remains)...);
    current.Future(std::forward<Args>(args)...);
  }

  template <typename TCurrent, typename... TRemains>
  auto Invoke(Args&&... args, TCurrent&& current, TRemains&&... remains)
      -> KATA_AOP_ONLY_BEFORE(TCurrent) {
    current.Before(std::forward<Args>(args)...);
    Invoke(std::forward<Args>(args)..., std::forward<TRemains>(remains)...);
  }

  template <typename TCurrent, typename... TRemains>
  auto Invoke(Args&&... args, TCurrent&& current, TRemains&&... remains)
      -> KATA_AOP_ONLY_FUTURE(TCurrent) {
    Invoke(std::forward<Args>(args)..., std::forward<TRemains>(remains)...);
    current.Future(std::forward<Args>(args)...);
  }

  //

  template <typename T>
  auto Invoke(Args&&... args, T&& aspect) -> KATA_AOP_BOTH(T) {
    aspect.Before(std::forward<Args>(args)...);
    m_func(std::forward<Args>(args)...);
    aspect.Future(std::forward<Args>(args)...);
  }

  template <typename T>
  auto Invoke(Args&&... args, T&& aspect) -> KATA_AOP_ONLY_BEFORE(T) {
    aspect.Before(std::forward<Args>(args)...);
    m_func(std::forward<Args>(args)...);
  }

  template <typename T>
  auto Invoke(Args&&... args, T&& aspect) -> KATA_AOP_ONLY_FUTURE(T) {
    m_func(std::forward<Args>(args)...);
    aspect.Future(std::forward<Args>(args)...);
  }
};

//

/**
 * Wrap the kernel function in list of aspects.
 * @tparam TAspects
 * @tparam F
 * @tparam Args
 * @param func
 * @param args
 */
template <typename... TAspects, typename F, typename... Args>
void aop(F&& func, Args&&... args) {
  Aop<F, Args...>(std::forward<F>(func))
      .Invoke(std::forward<Args>(args)..., identity_t<TAspects>()...);
}

}  // namespace kata

#endif  // KATA_AOP_H
