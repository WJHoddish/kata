// Created by Jiaheng on 2021/5/3.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

#ifndef KATA_FUNCTION_TRAITS_H
#define KATA_FUNCTION_TRAITS_H

#include "at.h"

namespace kata {

//

template <typename T>
struct function_traits;

template <typename R, typename... Args>
struct function_traits<R(Args...)> {
  template <std::size_t Idx>
  using arg_type    = at_t<Idx - 1, Args...>;
  using return_type = R;
  using args        = type_list<Args...>;

  //

  enum { arity = sizeof...(Args) };
};

template <typename R, typename... Args>
struct function_traits<R (*)(Args...)> : function_traits<R(Args...)> {
  ;  // function pointer
};

template <typename R, typename... Args>
struct function_traits<std::function<R(Args...)>>
    : function_traits<R(Args...)> {
  ;  // STL function
};

template <typename F>
struct function_traits : public function_traits<decltype(&F::operator())> {
  ;  // function object/functor
};

#define FUNCTION_TRAITS(...)                            \
  template <typename R, typename T, typename... Args>   \
  struct function_traits<R (T::*)(Args...) __VA_ARGS__> \
      : public function_traits<R(Args...)> {            \
    ;                                                   \
  };

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

}  // namespace kata

#endif  // KATA_FUNCTION_TRAITS_H
