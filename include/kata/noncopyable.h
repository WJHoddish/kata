// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_NONCOPYABLE_H
#define KATA_NONCOPYABLE_H

#define KATA_DISABLE_COPY_AND_ASSIGN(class_name) \
  class_name(const class_name&) = delete;        \
  class_name& operator=(const class_name&) = delete

namespace kata {

//

struct Noncopyable {
  Noncopyable() = default;

  KATA_DISABLE_COPY_AND_ASSIGN(Noncopyable);
};

}  // namespace kata

#endif  // KATA_NONCOPYABLE_H
