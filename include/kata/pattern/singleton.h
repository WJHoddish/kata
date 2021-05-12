// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Meyer's singleton.

#ifndef KATA_SINGLETON_H
#define KATA_SINGLETON_H

#include <kata/noncopyable.h>

#include <type_traits>

namespace kata {

//

template <typename T>
class Singleton : public Noncopyable {
 protected:
  struct token {
    ;
  };

 public:
  static T& get() noexcept(std::is_nothrow_constructible<T>::value) {
    static T _{token()};

    return _;
  }
};

}  // namespace kata

/**
 * If a class is designed to be a singleton, it ought not to require any
 * run-time dependencies while constructing!
 */

#define KATA_ENABLE_SINGLETON(class_name) \
  explicit class_name(typename Singleton<class_name>::token)

#define KATA_ENABLE_SINGLETON_TEMPLATE(class_name, ...) \
  explicit class_name(typename Singleton<class_name<__VA_ARGS__>>::token)

#endif  // KATA_SINGLETON_H
