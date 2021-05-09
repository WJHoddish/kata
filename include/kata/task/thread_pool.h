// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_THREAD_POOL_H
#define KATA_THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

namespace kata {

//

class ThreadPool {
  std::vector<std::thread>          workers_;
  std::queue<std::function<void()>> tasks_;
  std::condition_variable           cond_;
  std::mutex                        mtx_;
  bool                              stop_;

 public:
  explicit ThreadPool(std::size_t n = std::thread::hardware_concurrency())
      : stop_(false) {
    for (std::size_t i = 0; i < n; ++i) {
      workers_.emplace_back([this] {
        while (true) {
          std::function<void()> task;

          {
            std::unique_lock<std::mutex> guard(mtx_);

            cond_.wait(guard, [this] { return stop_ || !tasks_.empty(); });

            // pool's already stopped & no unfinished task
            if (stop_ && tasks_.empty()) return;

            // pick a task from queue
            task = std::move(tasks_.front());
            tasks_.pop();
          }

          // run task
          task();
        }
      }  ///< thread function
      );
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> guard(mtx_);

      stop_ = true;
    }

    // notify all waiting threads to join
    cond_.notify_all();
    for (std::thread& worker : workers_) worker.join();
  }

  //

  template <class F,
            class... Args,
            typename R = typename std::result_of<F(Args...)>::type>
  std::future<R> enqueue(F&& f, Args&&... args) {
    auto task = std::make_shared<std::packaged_task<R()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<R> res = task->get_future();

    // add task to queue
    {
      std::unique_lock<std::mutex> guard(mtx_);
      if (stop_) throw;  // enqueue on stopped pool
      tasks_.emplace([task]() { (*task)(); });
    }

    cond_.notify_one();
    return res;
  }
};

}  // namespace kata

#endif  // KATA_THREAD_POOL_H
