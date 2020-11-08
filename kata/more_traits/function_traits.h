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

template <typename R, typename... Args>
struct function_traits<R(Args...)> {
  template <uint64_t I>
  struct args {
    static_assert(I < sizeof...(Args), "index is out of range");

    /**
     *
     */

    using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
  };

  /**
   * <R> has 3 variants.
   */

  typedef R return_type;
  typedef R function_type(Args...);
  typedef R (*pointer)(Args...);

  /**
   *
   */

  typedef std::tuple<std::remove_cv_t<std::remove_reference_t<Args>>...>
      tuple_type;

  typedef std::tuple<std::remove_const_t<std::remove_reference_t<Args>>...>
      tuple_type_bare;

  using stl_function_type = std::function<function_type>;
};

template <typename R, typename... Args>
struct function_traits<R (*)(Args...)> : function_traits<R(Args...)> {
  /**
   *
   */
};

template <typename R, typename... Args>
struct function_traits<std::function<R(Args...)>>
    : function_traits<R(Args...)> {
  /**
   *
   */
};

template <typename T>
struct function_traits : function_traits<decltype(&T::operator())> {
  /**
   *
   */
};

} // namespace kata

#endif // KATA_FUNCTION_TRAITS_H
