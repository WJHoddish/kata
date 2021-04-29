// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Singleton based on CRTP idiom & C++ Magic Static.

#ifndef KATA_SINGLETON_H
#define KATA_SINGLETON_H

#include <kata/noncopyable.h>

#include <type_traits>

namespace kata {

//

template <typename T>
class Singleton : public Noncopyable {
 public:
  static T& get() noexcept(std::is_nothrow_constructible<T>::value) {
    static T _{token()};  ///< instance the unique existence

    return _;
  }

 protected:
  struct token {};
};

}  // namespace kata

/**
 * Select one command to enable singleton, followed by constructor body...
 */

#define ENABLE_SINGLETON(class_name)        \
  friend class kata::Singleton<class_name>; \
  explicit class_name(typename kata::Singleton<class_name>::token)

#define ENABLE_SINGLETON_TEMPLATE(class_name, ...)       \
  friend class kata::Singleton<class_name<__VA_ARGS__>>; \
  explicit class_name(typename kata::Singleton<class_name<__VA_ARGS__>>::token)

/**
 * If a class is designed to be a singleton, it ought not to require any
 * dependencies while constructing!
 */

#endif  // KATA_SINGLETON_H
