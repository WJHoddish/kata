// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Automatically-joining task.

#ifndef KATA_JOINING_THREAD_H
#define KATA_JOINING_THREAD_H

#include <thread>

namespace kata {

//

class JoiningThread {
  std::thread m_t;  ///< C++11 thread

 public:
  template <typename F, typename... Args>
  explicit JoiningThread(F&& func, Args&&... args)
      : m_t(std::forward<F>(func), std::forward<Args>(args)...) {
    ;
  }

  explicit JoiningThread(std::thread t)
      : m_t(std::move(t)) {
    ;
  }

  JoiningThread(JoiningThread&& src) noexcept
      : m_t(std::move(src.m_t)) {
    ;
  }

  JoiningThread& operator=(JoiningThread&& rhs) noexcept {
    if (joinable()) join();    // make own task joined
    m_t = std::move(rhs.m_t);  // absorb the foreign one
    return *this;
  }

  JoiningThread& operator=(std::thread&& t) noexcept {
    if (joinable()) join();
    m_t = std::move(t);
    return *this;
  }

  ~JoiningThread() {
    if (joinable()) join();  // RAII
  }

  //

  void swap(JoiningThread&& src) { m_t.swap(src.m_t); }

  bool joinable() const noexcept { return m_t.joinable(); }

  void join() { m_t.join(); }

  void detach() { m_t.detach(); }

  std::thread::id get_id() { return m_t.get_id(); }
};

}  // namespace kata

#endif  // KATA_JOINING_THREAD_H
