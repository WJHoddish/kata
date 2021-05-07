// Created by Jiaheng on 2021/5/7.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_VISITOR_H
#define KATA_VISITOR_H

namespace kata {

//

template <typename... Args>
struct visitor;

template <typename T, typename... Args>
struct visitor<T, Args...> : visitor<Args...> {
  using visitor<Args...>::Visit;

  virtual void Visit(const T&) = 0;
};

template <typename T>
struct visitor<T> {
  virtual void Visit(const T&) = 0;
};

}  // namespace kata

#endif  // KATA_VISITOR_H
