// Created by Jiaheng on 2021/5/12.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_REPEAT_POOL_H
#define KATA_REPEAT_POOL_H

#include <kata/task/repeat_pool/worker_pool.h>

#include <functional>

namespace kata {

//

class RepeatPool {
  struct FnTask : public Task {
    const std::function<void(std::size_t, std::size_t)>* fn{};
    std::size_t                                          id{};
    std::size_t                                          begin{};
    std::size_t                                          end{};

    void Run() override {
      for (std::size_t i = begin; i < end; ++i) (*fn)(id, i);
    }
  };

  unsigned                           m_min_threads;
  unsigned                           m_num_threads;
  std::shared_ptr<WorkersPool>       m_workers_pool;
  std::vector<std::shared_ptr<Task>> m_tasks;
  mutable std::mutex                 m_mtx;

 public:
  explicit RepeatPool(unsigned n = std::thread::hardware_concurrency())
      : m_min_threads(n)
      , m_num_threads(n)
      , m_workers_pool(std::make_shared<WorkersPool>()) {
    ;
  }

  //

  void Run(const std::function<void(std::size_t, std::size_t)>& fn,
           std::size_t                                          range) {
    std::lock_guard<std::mutex> guard(m_mtx);

    const std::size_t units_per_thread =
        (range + m_num_threads - 1) / m_num_threads;

    // prepare tasks for threads
    m_tasks.resize(m_num_threads);
    for (std::size_t i = 0; i < m_num_threads; ++i) {
      if (!m_tasks[i]) m_tasks[i].reset(new FnTask());

      auto* task = (FnTask*)m_tasks[i].get();
      {
        task->fn    = &fn;
        task->id    = i;
        task->begin = std::min<std::size_t>(range, units_per_thread * i);
        task->end   = std::min<std::size_t>(range, units_per_thread * (i + 1));
      }

      if (task->begin >= task->end) {
        m_tasks.resize(i);
        break;
      }
    }

    // pass the pool a package of tasks
    m_workers_pool->Execute(m_tasks);
  }
};

}  // namespace kata

#endif  // KATA_REPEAT_POOL_H
