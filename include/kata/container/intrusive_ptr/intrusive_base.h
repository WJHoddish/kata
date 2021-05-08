// Created by Jiaheng on 2021/5/8.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_INTRUSIVE_BASE_H
#define KATA_INTRUSIVE_BASE_H

#include "weak_view_template.h"

namespace kata {

//

template <typename T, class D = std::default_delete<T>>
class intrusive_base : public _intrusive_ptr::ref_count_base, private D {
  using weak_view =
      _intrusive_ptr::weak_view_template<typename std::remove_cv<T>::type>;

  mutable std::atomic<weak_view *> view_;

 protected:
  template <typename U, typename V>
  static intrusive_ptr<U> fork_strong(V *t) noexcept {
    const auto u = static_cast_or_dynamic_cast<U *>(t);
    if (!u) return nullptr;
    u->ref_count_base::add_ref();  // ref++
    return intrusive_ptr<U>(u);
  }

  template <typename U, typename V>
  static intrusive_weak_ptr<U> fork_weak(V *t) noexcept {
    const auto u = static_cast_or_dynamic_cast<U *>(t);
    if (!u) return nullptr;
    return intrusive_weak_ptr<U>(u);
  }

 public:
  constexpr intrusive_base() noexcept
      : _intrusive_ptr::ref_count_base()
      , D()
      , view_(nullptr) {
    ;
  }

  constexpr intrusive_base(const intrusive_base &) noexcept
      : intrusive_base() {
    ;
  }

  intrusive_base &operator=(const intrusive_base &) noexcept { return *this; }

  ~intrusive_base() {
    const auto v = view_.load(std::memory_order_consume);

    if (v) {
      if (v->_intrusive_ptr::ref_count_base::sub_ref())
        delete v;
      else
        v->unlink();
    }
  }

  //

  const D &get_deleter() const noexcept { return *this; }

  D &get_deleter() noexcept { return *this; }

  bool unique() const volatile noexcept {
    return _intrusive_ptr::ref_count_base::__unique();
  }

  long use_count() const volatile noexcept {
    return _intrusive_ptr::ref_count_base::get_ref();
  }

  long weak_count() const volatile noexcept {
    const auto v = get_weak_view();

    return !v ? 0 : v->_intrusive_ptr::ref_count_base::get_ref() - 1;
  }

  void reserve_weak() const volatile { require_weak_view(); }

 private:
  weak_view *get_weak_view() const volatile noexcept {
    auto v = view_.load(std::memory_order_consume);

    return v;
  }

  weak_view *require_weak_view() const volatile {
    auto v = view_.load(std::memory_order_consume);

    if (!v) {
      const auto t = static_cast_or_dynamic_cast<const volatile T *>(this);
      if (!t) throw std::bad_cast();
      const auto new_v = new weak_view(const_cast<T *>(t));
      if (view_.compare_exchange_strong(
              v, new_v, std::memory_order_release, std::memory_order_consume)) {
        v = new_v;
      } else {
        delete new_v;
      }
    }
    return v;
  }
};

}  // namespace kata

#endif  // KATA_INTRUSIVE_BASE_H
