// Copyright (c) 2020/11/6 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//
// Task manager.

#ifndef KATA_THREAD_POOL_H
#define KATA_THREAD_POOL_H

#include "../utils/lock.h"
#include <functional>
#include <queue>
#include <vector>

namespace kata {
class ThreadPool {
public:
private:
  std::queue<std::function<void()>> tasks_;
  std::vector<std::thread>          workers_;

  /**
   * Thread pool control.
   */

  std::mutex              mtx_;
  std::condition_variable cond_;
  bool                    stop_; // shut down
};

} // namespace kata

#endif
