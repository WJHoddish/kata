// Created by Jiaheng on 2021/5/12.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_WORKER_POOL_H
#define KATA_WORKER_POOL_H

#include <kata/alloc.h>
#include <kata/noncopyable.h>

#include <thread>
#include <vector>

#include "blocking_counter.h"

namespace kata {

//

struct Task {
  Task()             = default;
  virtual ~Task()    = default;
  virtual void Run() = 0;
};

//

class alignas(kCacheLineSize) Worker {
  enum class State : uint8_t {
    ThreadStartup,  ///< initial state (before the thread main loop runs)
    Ready,          ///< not working and no task assigned
    HasWork,        ///< has work to do
    ExitAsSoonAsPossible
  };

  std::unique_ptr<std::thread> m_thd;
  std::atomic<Task*>           m_task;  ///< his own task
  std::atomic<State>           m_state;
  /**
   * The condition variable and mutex that guard "state changes".
   */
  std::condition_variable      m_cond;
  std::mutex                   m_mtx;
  /**
   * The scheduler of master's thread, which will notify master when this worker
   * is "Ready". There are 2 ways to get a worker "Ready": finishing his own
   * task; just being initialized.
   */
  BlockingCounter* const       m_blocking_counter;

 public:
  explicit Worker(BlockingCounter* blocking_counter)
      : m_task(nullptr)
      , m_state(State::ThreadStartup)
      , m_blocking_counter(blocking_counter) {
    m_thd = std::make_unique<std::thread>([this]() { this->ThreadFunc(); });
  }

  ~Worker() {
    ChangeState(State::ExitAsSoonAsPossible);
    m_thd->join();
  }

  //

  void ThreadFunc() {
    ChangeState(State::Ready);

    while (true) {
      State temp =
          WaitForVariableChange(State::Ready, &m_state, &m_cond, &m_mtx);

      switch (temp) {
        case State::HasWork:
          (*m_task).Run();
          m_task = nullptr;
          ChangeState(State::Ready);  // update state & signal master
          break;
        case State::ExitAsSoonAsPossible:
          return;
        default:
          abort();
      }
    }
  }

  void ChangeState(State state) {
    std::lock_guard<std::mutex> guard(m_mtx);

    // transitions between some states are illegal
    switch (m_state.load(std::memory_order_relaxed)) {
      case State::ThreadStartup:
        break;
      case State::Ready:
        break;
      case State::HasWork:
        break;
      default:
        abort();
    }

    // update state
    m_state.store(state, std::memory_order_relaxed);

    m_cond.notify_one();

    // signal master
    if (state == State::Ready) m_blocking_counter->DecrementCount();
  }

  void StartWork(Task* task) {
    m_task = task;
    ChangeState(State::HasWork);
  }
};

//

class WorkersPool : public Noncopyable {
  std::vector<aligned_ptr_t<Worker>> m_workers;
  BlockingCounter                    m_blocking_counter;

  void CreateWorkers(std::size_t n) {
    // no need for more workers
    if (m_workers.size() >= n) return;

    m_blocking_counter.Reset(n - m_workers.size());

    // each worker starts a new thread while establishing
    while (m_workers.size() < n)
      m_workers.push_back(make_aligned<Worker>(&m_blocking_counter));

    // wait all new workers being settled (state change)
    m_blocking_counter.Wait();
  }

 public:
  void Execute(const std::vector<std::shared_ptr<Task>>& tasks) {
    std::size_t n = tasks.size() - 1;

    CreateWorkers(n);
    m_blocking_counter.Reset(n);

    // run all tasks
    for (std::size_t i = 1; i < tasks.size(); ++i)
      m_workers[i - 1]->StartWork(tasks[i].get());

    // run one of them on this thread
    auto& task = tasks.front();
    task->Run();

    // wait for all tasks to have finished working
    m_blocking_counter.Wait();
  }
};

}  // namespace kata

#endif  // KATA_WORKER_POOL_H
