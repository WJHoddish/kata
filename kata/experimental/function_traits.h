// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Extract type info of functions/functors.

#ifndef KATA_FUNCTION_TRAITS_H
#define KATA_FUNCTION_TRAITS_H

#include <functional>

namespace kata {
template <typename T>
struct function_traits;

template <typename R, typename... Args>
struct function_traits<R(Args...)> {
  enum { arity = sizeof...(Args) };

  typedef R (*pointer)(Args...);
  typedef std::function<R(Args...)> stl_function;

  template <std::size_t I>
  struct args {
    static_assert(I < arity, "out of range index");

    using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
  };
};

// function pointer
template <typename R, typename... Args>
struct function_traits<R (*)(Args...)> : public function_traits<R(Args...)> {};

// functor
template <typename F>
struct function_traits : public function_traits<decltype(&F::operator())> {};

// STL function object
template <typename R, typename... Args>
struct function_traits<std::function<R(Args...)>>
    : public function_traits<R(Args...)> {};

// member function
#define FUNCTION_TRAITS(...)                                                   \
  template <typename R, typename T, typename... Args>                          \
  struct function_traits<R (T::*)(Args...) __VA_ARGS__>                        \
      : public function_traits<R(Args...)> {};

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

// helper functions:
template <typename F, typename R = typename function_traits<F>::pointer>
auto to_function_pointer(const F& lambda) {
  return static_cast<R>(lambda);
}

template <typename F, typename R = typename function_traits<F>::stl_function>
auto to_function(const F& lambda) {
  return static_cast<R>(lambda);
}

template <typename F, typename R = typename function_traits<F>::stl_function>
auto to_function(F&& lambda) {
  return static_cast<R>(std::forward<F>(lambda));
}

} // namespace kata

#endif // KATA_FUNCTION_TRAITS_H
