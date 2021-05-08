// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Make derived classes cannot be copied.

#ifndef KATA_NONCOPYABLE_H
#define KATA_NONCOPYABLE_H

namespace kata {

//

struct Noncopyable {
  Noncopyable(const Noncopyable&) = delete;
  Noncopyable& operator=(const Noncopyable&) = delete;
};

}  // namespace kata

#endif  // KATA_NONCOPYABLE_H
