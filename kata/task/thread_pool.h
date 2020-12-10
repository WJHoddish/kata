// Copyright (c) 2020/11/6 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//
// Task manager.

#ifndef KATA_THREAD_POOL_H
#define KATA_THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace kata {
class ThreadPool {
  using Task = std::function<void()>;

public: // structors
  /**
   * Start the pool after initiating all thread.
   *
   * @param _Num number of threads
   */
  explicit ThreadPool(std::size_t _Num)
      : stop_{false} {
    for (std::size_t i = 0; i < _Num; ++i) {
      workers_.emplace_back(
          // create a new thread
          [this] {
            while (!stop_) {
              Task task;

              {
                std::unique_lock<std::mutex> lock(
                    queue_mtx_); // release when leaving this block

                // lock
                condition_.wait(lock, [this] {
                  // NOTE: Condition: false => continue; true => break.
                  return (stop_ || !tasks_.empty());
                });

                // all tasks are completed
                if (stop_ && tasks_.empty()) return;

                // fetch out a task from queue
                task = std::move(tasks_.front());
                tasks_.pop();
              }

              task();
            }
          });
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(queue_mtx_);
      stop_ = true;
    }

    // let all threads check the condition
    condition_.notify_all();

    // recall all threads in this main thread
    for (std::thread& worker : workers_) worker.join();
  }

public: // modifier
  /**
   * Push a new task into the queue.
   *
   * @tparam F
   * @tparam Args
   * @tparam R
   * @param f
   * @param args
   * @return
   */
  template <typename F, typename... Args,
            typename R = typename std::result_of<F(Args...)>::type>
  auto enqueue(F&& f, Args&&... args) -> std::future<R> {
    auto task = std::make_shared<std::packaged_task<R()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<R> res = task->get_future();

    {
      std::unique_lock<std::mutex> lock(queue_mtx_);

      // adding task after stopping the pool is NOT allowed
      if (stop_) throw std::runtime_error("enqueue on stopped ThreadPool");

      tasks_.emplace([task]() { (*task)(); });
    }

    condition_.notify_one();
    return res;
  }

private:
  std::vector<std::thread> workers_;
  std::queue<Task>         tasks_;
  std::mutex               queue_mtx_;
  std::condition_variable  condition_;
  bool                     stop_;
};

} // namespace kata

#endif
