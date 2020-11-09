// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//
// Cast kinds of function objects through tmp.

#ifndef KATA_FUNCTION_TRAITS_H
#define KATA_FUNCTION_TRAITS_H

#include <functional>

namespace kata {
template <typename T>
struct function_traits;

/**
 * Specifying a function only needs <R> and <Args...>, here is a class for the
 * "abstraction of function segments", which got 3 partial specializations.
 *
 * @tparam R
 * @tparam Args
 */
template <typename R, typename... Args>
struct function_traits<R(Args...)> {
  template <uint64_t I>
  struct args {
    static_assert(I < sizeof...(Args), "index is out of range");

    using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
  };

  /**
   * Derive such concepts from <R> and <Args...>:
   */

  typedef R (*pointer)(Args...); // c-style function pointer

  typedef R function_type(Args...);
  using stl_function_type = std::function<function_type>;

  typedef std::tuple<std::remove_cv_t<std::remove_reference_t<Args>>...>
      tuple_type;

  typedef std::tuple<std::remove_const_t<std::remove_reference_t<Args>>...>
      tuple_type_bare;
};

/**
 *
 * @tparam R
 * @tparam Args
 */
template <typename R, typename... Args>
struct function_traits<R (*)(Args...)> : function_traits<R(Args...)> {};

/**
 *
 * @tparam R
 * @tparam Args
 */
template <typename R, typename... Args>
struct function_traits<std::function<R(Args...)>>
    : function_traits<R(Args...)> {};

/**
 *
 * @tparam T
 */
template <typename T>
struct function_traits : function_traits<decltype(&T::operator())> {};

//

template <typename F, typename R = typename function_traits<F>::pointer>
R to_function_pointer(const F& lambda) {
  return static_cast<R>(lambda);
}

template <typename F,
          typename R = typename function_traits<F>::stl_function_type>
R to_function(const F& lambda) {
  return static_cast<R>(lambda);
}

template <typename F,
          typename R = typename function_traits<F>::stl_function_type>
R to_function(F&& lambda) {
  return static_cast<R>(std::forward<F>(lambda));
}

} // namespace kata

#define FUNCTION_TRAITS(...)                                                   \
  template <typename R, typename ClassType, typename... Args>                  \
  struct kata::function_traits<R (ClassType::*)(Args...) __VA_ARGS__>          \
      : function_traits<R(Args...)> {};

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

#endif // KATA_FUNCTION_TRAITS_H
