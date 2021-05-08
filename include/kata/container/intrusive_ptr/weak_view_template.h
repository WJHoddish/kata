// Created by Jiaheng on 2021/5/8.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_WEAK_VIEW_TEMPLATE_H
#define KATA_WEAK_VIEW_TEMPLATE_H

#include <kata/more_traits/static_cast_or_dynamic_cast.h>
#include <kata/noncopyable.h>

#include <mutex>

#include "ref_count_base.h"

namespace kata::_intrusive_ptr {

//

template <typename T>
class weak_view_template : public ref_count_base, public Noncopyable {
  mutable std::mutex mtx_;
  T*                 parent_;

 public:
  explicit constexpr weak_view_template(T* parent) noexcept
      : ref_count_base()
      , mtx_()
      , parent_(parent) {
    ;
  }

  //

  bool expired() const noexcept {
    const std::lock_guard<std::mutex> guard(mtx_);
    const auto                        p = parent_;

    return !p ? true : p->ref_count_base::get_ref() == 0;
  }

  template <typename U>
  intrusive_ptr<U> lock() const noexcept {
    const std::lock_guard<std::mutex> guard(mtx_);
    const auto u = static_cast_or_dynamic_cast<U*>(parent_);

    if (!u) return nullptr;

    if (!u->ref_count_base::try_add_ref()) return nullptr;

    return intrusive_ptr<U>(u);
  }

  void unlink() noexcept {
    const std::lock_guard<std::mutex> guard(mtx_);

    parent_ = nullptr;
  }
};

}  // namespace kata::_intrusive_ptr

#endif  // KATA_WEAK_VIEW_TEMPLATE_H
