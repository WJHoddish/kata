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
  std::queue<std::function<void()>> m_tasks;  ///< task queue
  std::vector<std::thread>          m_doers;
  std::condition_variable           m_cond;
  std::mutex                        m_mtx;
  bool                              m_stop;

 public:
  explicit ThreadPool(std::size_t n = std::thread::hardware_concurrency())
      : m_stop(false) {
    for (std::size_t i = 0; i < n; ++i) {
      // start thread function
      m_doers.emplace_back([this] {
        while (true) {
          std::function<void()> task;

          {
            std::unique_lock<std::mutex> guard(m_mtx);
            m_cond.wait(
                guard,
                [this] { return m_stop || !m_tasks.empty(); }  // until reached
            );

            // pool's already settled down
            if (m_stop && m_tasks.empty()) return;

            // pick a task from queue
            task = std::move(m_tasks.front());
            m_tasks.pop();
          }

          task();  // run task
        }
      });
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> guard(m_mtx);

      m_stop = true;
    }

    // notify all waiting threads to join
    m_cond.notify_all();
    for (std::thread& doer : m_doers) doer.join();
  }

  //

  template <class F, class... Args, typename R = std::result_of_t<F(Args...)>>
  auto Enqueue(F&& f, Args&&... args) {
    auto task = std::make_shared<std::packaged_task<R()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    // acquire asynchronous operation result
    std::future<R> fu = task->get_future();

    // add task to queue
    {
      std::unique_lock<std::mutex> guard(m_mtx);

      if (m_stop) throw;  // enqueue on stopped pool
      m_tasks.emplace([task]() { (*task)(); });
    }

    m_cond.notify_one();

    return fu;
  }
};

}  // namespace kata

#endif  // KATA_THREAD_POOL_H
