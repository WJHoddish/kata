// Copyright (c) 2020/11/6 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//
// Object pool made of fixed-size slots, an example of singleton.

#ifndef KATA_SLOT_POOL_H
#define KATA_SLOT_POOL_H

#include "singleton.h"

namespace kata {
template <typename T, unsigned int PAGE_SIZE = 1024>
class SlotPool : public Singleton<SlotPool<T, PAGE_SIZE>> {
  ENABLE_SINGLETON_TEMPLATE(SlotPool, T, PAGE_SIZE) {
    // NOTE: Singleton, only init once, alloc a page.
  }
};

} // namespace kata

#endif
