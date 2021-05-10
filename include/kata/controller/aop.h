// Created by Jiaheng on 2021/5/10.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

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

KATA_AOP_MEMBER(Kernel)
KATA_AOP_MEMBER(Before)
KATA_AOP_MEMBER(Future)

namespace kata {

//

template <typename F, typename... Args>
struct Aop : Noncopyable {
  F m_f;

  explicit Aop(F&& f)
      : m_f(std::forward<F>(f)) {
    ;
  }

  template <typename TCurrent, typename... TRemains>
  typename std::enable_if<has_member_Before<TCurrent, Args...>::value &&
                          has_member_Future<TCurrent, Args...>::value>::type
  Invoke(Args&&... args,
         TCurrent&& current_aspect,
         TRemains&&... remains_aspect) {
    current_aspect.Before(std::forward<Args>(args)...);
    Invoke(std::forward<Args>(args)...,
           std::forward<TRemains>(remains_aspect)...);
    current_aspect.Future(std::forward<Args>(args)...);
  }

  template <typename TCurrent, typename... TRemains>
  typename std::enable_if<!has_member_Before<TCurrent, Args...>::value &&
                          has_member_Future<TCurrent, Args...>::value>::type
  Invoke(Args&&... args,
         TCurrent&& current_aspect,
         TRemains&&... remains_aspect) {
    Invoke(std::forward<Args>(args)...,
           std::forward<TRemains>(remains_aspect)...);
    current_aspect.Future(std::forward<Args>(args)...);
  }

  template <typename TCurrent, typename... TRemains>
  typename std::enable_if<has_member_Before<TCurrent, Args...>::value &&
                          !has_member_Future<TCurrent, Args...>::value>::type
  Invoke(Args&&... args,
         TCurrent&& current_aspect,
         TRemains&&... remains_aspect) {
    current_aspect.Before(std::forward<Args>(args)...);
    Invoke(std::forward<Args>(args)...,
           std::forward<TRemains>(remains_aspect)...);
  }

  //

  template <typename T>
  typename std::enable_if<has_member_Before<T, Args...>::value &&
                          has_member_Future<T, Args...>::value>::type
  Invoke(Args&&... args, T&& aspect) {
    aspect.Before(std::forward<Args>(args)...);
    m_f(std::forward<Args>(args)...);
    aspect.Future(std::forward<Args>(args)...);
  }

  template <typename T>
  typename std::enable_if<has_member_Before<T, Args...>::value &&
                          !has_member_Future<T, Args...>::value>::type
  Invoke(Args&&... args, T&& aspect) {
    aspect.Before(std::forward<Args>(args)...);
    m_f(std::forward<Args>(args)...);
  }

  template <typename T>
  typename std::enable_if<!has_member_Before<T, Args...>::value &&
                          has_member_Future<T, Args...>::value>::type
  Invoke(Args&&... args, T&& aspect) {
    m_f(std::forward<Args>(args)...);
    aspect.Future(std::forward<Args>(args)...);
  }
};

//

template <typename... TAspects, typename F, typename... Args>
void aop(F&& f, Args&&... args) {
  Aop<F, Args...>(std::forward<F>(f))
      .Invoke(std::forward<Args>(args)..., identity_t<TAspects>()...);
}

}  // namespace kata

#endif  // KATA_AOP_H
