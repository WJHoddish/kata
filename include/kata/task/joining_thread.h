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
  std::thread t_;  ///< thread

 public:
  template <typename F, typename... Args>
  explicit JoiningThread(F&& func, Args&&... args)
      : t_(std::forward<F>(func), std::forward<Args>(args)...) {
    ;
  }

  explicit JoiningThread(std::thread t)
      : t_(std::move(t)) {
    ;
  }

  JoiningThread(JoiningThread&& src) noexcept
      : t_(std::move(src.t_)) {
    ;
  }

  JoiningThread& operator=(JoiningThread&& src) noexcept {
    if (joinable()) join();  // make own task joined
    t_ = std::move(src.t_);  // absorb the foreign one
    return *this;
  }

  JoiningThread& operator=(std::thread&& t) noexcept {
    if (joinable()) join();
    t_ = std::move(t);
    return *this;
  }

  ~JoiningThread() {
    if (joinable()) join();  // RAII
  }

  //

  void swap(JoiningThread&& src) { t_.swap(src.t_); }

  bool joinable() const noexcept { return t_.joinable(); }

  void join() { t_.join(); }

  void detach() { t_.detach(); }

  std::thread::id get_id() { return t_.get_id(); }
};

}  // namespace kata

#endif  // KATA_JOINING_THREAD_H
