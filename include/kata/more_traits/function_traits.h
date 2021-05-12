// Created by Jiaheng on 2021/5/3.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//
// Extract function type information.

#ifndef KATA_FUNCTION_TRAITS_H
#define KATA_FUNCTION_TRAITS_H

#include <kata/more_traits/at.h>

#include <functional>

namespace kata {

//

template <typename T>
struct function_traits;

template <typename R, typename... Args>
class function_traits<R(Args...)> {
  typedef R F(Args...);

 public:
  template <std::size_t Idx>
  using arg_type      = at_t<Idx - 1, Args...>;
  using return_type   = R;
  using function_type = std::function<F>;
  using args          = type_list<Args...>;

  enum { arity = sizeof...(Args) };
};

template <typename F>
struct function_traits : public function_traits<decltype(&F::operator())> {
  ;  // functor (lambda expression)
};

template <typename R, typename... Args>
struct function_traits<R (*)(Args...)> : public function_traits<R(Args...)> {
  ;  // function pointer
};

template <typename R, typename... Args>
struct function_traits<std::function<R(Args...)>>
    : public function_traits<R(Args...)> {
  ;  // STL function
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

//

template <typename F>
using function_type_t = typename function_traits<F>::function_type;

//

template <typename F>
constexpr auto to_function(const F& f) {
  return static_cast<function_type_t<F>>(f);  // lambda => STL function
}

template <typename F>
constexpr auto to_function(F&& f) {
  return static_cast<function_type_t<F>>(std::forward<F>(f));
}

}  // namespace kata

#endif  // KATA_FUNCTION_TRAITS_H
