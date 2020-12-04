// Copyright (c) 2020/11/6 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//
// Task manager.

#ifndef KATA_THREAD_POOL_H
#define KATA_THREAD_POOL_H

#include <functional>
#include <queue>
#include <vector>

#include "lock.h"

namespace kata {
class ThreadPool {
  std::vector<std::thread>          workers_;
  std::queue<std::function<void()>> tasks_;
  std::mutex                        mtx_;
  std::condition_variable           cv_;
  bool                              stop_;

public:
};

// TODO(Jiaheng): Consider singleton.

} // namespace kata

#endif
