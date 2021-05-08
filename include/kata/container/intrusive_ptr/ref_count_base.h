// Created by Jiaheng on 2021/5/8.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_REF_COUNT_BASE_H
#define KATA_REF_COUNT_BASE_H

#include <atomic>
#include <exception>
#include <memory>

namespace kata {

//

template <typename T>
class intrusive_ptr;

template <typename T>
class intrusive_weak_ptr;

}  // namespace kata

namespace kata::_intrusive_ptr {

//

class ref_count_base {
  mutable std::atomic<long> ref_;

 protected:
  constexpr ref_count_base() noexcept
      : ref_(1) {
    ;
  }

  constexpr ref_count_base(const ref_count_base &) noexcept
      : ref_count_base() {
    ;
  }

  ref_count_base &operator=(const ref_count_base &) noexcept { return *this; }

  ~ref_count_base() {
    if (ref_.load(std::memory_order_relaxed) > 1) std::terminate();
  }

 public:
  bool __unique() const volatile noexcept {
    return ref_.load(std::memory_order_relaxed) == 1;
  }

  long get_ref() const volatile noexcept {
    return ref_.load(std::memory_order_relaxed);
  }

  bool add_ref() const volatile noexcept {
    ref_.fetch_add(1, std::memory_order_relaxed);
  }

  bool sub_ref() const volatile noexcept {
    ref_.fetch_sub(1, std::memory_order_relaxed);
  }

  //

  bool try_add_ref() const volatile noexcept {
    auto old = ref_.load(std::memory_order_relaxed);

    do {
      if (old == 0) return false;
    } while (
        !ref_.compare_exchange_strong(old, old + 1, std::memory_order_relaxed));

    return true;
  }
};

}  // namespace kata::_intrusive_ptr

#endif  // KATA_REF_COUNT_BASE_H
