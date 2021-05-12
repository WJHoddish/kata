// Created by Jiaheng on 2021/5/11.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// CRTP-based object counter

#ifndef KATA_OBJECT_COUNTER_H
#define KATA_OBJECT_COUNTER_H

#include <cstddef>

namespace kata {

//

template <typename T>
class ObjectCounter {
  std::size_t Increase() { return (++ObjectCounter<T>::m_cnt); }
  std::size_t Decrease() { return (--ObjectCounter<T>::m_cnt); }

 protected:
  static std::size_t m_cnt;

 public:
  ObjectCounter() { Increase(); }
  ObjectCounter(const ObjectCounter<T>&) { Increase(); }
  ~ObjectCounter() { Decrease(); }
};

template <typename T>
std::size_t ObjectCounter<T>::m_cnt = 0;

}  // namespace kata

#endif  // KATA_OBJECT_COUNTER_H
