// Created by Jiaheng on 2021/5/12.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_BLOCKING_COUNTER_H
#define KATA_BLOCKING_COUNTER_H

#include <atomic>
#include <condition_variable>

namespace kata {

//

template <typename T>
T WaitForVariableChange(T                        old_value,
                        std::atomic<T>*          src,
                        std::condition_variable* cond,
                        std::mutex*              mtx) {
  std::unique_lock<std::mutex> guard(*mtx);

  T new_value = src->load(std::memory_order_relaxed);

  cond->wait(guard, [&]() {
    new_value = src->load(std::memory_order_relaxed);
    return new_value != old_value;
  });

  return new_value;
}

//

class BlockingCounter {
  std::atomic<std::size_t> m_cnt{0};  ///< countdown
  std::condition_variable  m_cond;
  std::mutex               m_mtx;

 public:
  void Wait() {
    while (std::size_t cnt = m_cnt.load(std::memory_order_relaxed)) {
      WaitForVariableChange(cnt,
                            &m_cnt,
                            &m_cond,
                            &m_mtx);  // block when countdown remains unchanged
    }                                 // break when countdown decreases to 0
  }

  void Reset(std::size_t n) {
    std::lock_guard<std::mutex> guard(m_mtx);

    if (m_cnt) throw;  // countdown before resetting must be 0
    m_cnt = n;
  }

  bool DecrementCount() {
    const auto cnt = m_cnt.fetch_sub(1, std::memory_order_relaxed) - 1;

    if (cnt == 0) {
      std::lock_guard<std::mutex> guard(m_mtx);

      m_cond.notify_one();
    }

    return (cnt == 0);
  }
};

}  // namespace kata

#endif  // KATA_BLOCKING_COUNTER_H
