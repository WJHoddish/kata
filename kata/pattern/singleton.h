// Copyright (c) 2020/11/6 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//
// Singleton, the design pattern, which is a base class stands in a CRTP idiom,
// using C++ Magic Static.

#ifndef KATA_SINGLETON_H
#define KATA_SINGLETON_H

#include "../utils/noncopyable.h"
#include <type_traits>

namespace kata {
template <typename T>
class Singleton : public NonCopyable {
public:
  /**
   * Get the unique instance of <T>: If the control enters the declaration
   * concurrently while the variable is being initialized, the concurrent
   * execution shall wait for completion of the initialization.
   *
   * @return
   */
  static T& get() noexcept(std::is_nothrow_constructible<T>::value) {
    static T /*constructor of <T> requires a token as dependency*/ _{token()};

    return _;
  }

protected:
  struct token {};

  Singleton() noexcept = default;
};

} // namespace kata

/**
 * Select one of these commands to enable singleton for your custom class.
 */

#define ENABLE_SINGLETON(class_name)                                           \
  friend class Singleton<class_name>;                                          \
  explicit class_name(                                                         \
      typename Singleton<class_name>::token) /*constructor body*/

#define ENABLE_SINGLETON_TEMPLATE(class_name, ...)                             \
  friend class Singleton<class_name<__VA_ARGS__>>;                             \
  explicit class_name(                                                         \
      typename Singleton<class_name<__VA_ARGS__>>::token) /*constructor body*/

#endif