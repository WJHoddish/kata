// Copyright (c) 2020/11/9 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//
// A garbage collector is triggered when an exception occurs in try blocks.

#ifndef KATA_SCOPE_GUARD_H
#define KATA_SCOPE_GUARD_H

#include <type_traits>
#include <utility>

namespace kata {
template <typename F>
class ScopeGuard {
public: // structors
  explicit ScopeGuard(const F& f)
      : func_(f)
      , dismiss_(false) {}

  explicit ScopeGuard(F&& f)
      : func_(std::move(f))
      , dismiss_(false) {}

  ScopeGuard(ScopeGuard&& _Rhs) noexcept
      : func_(std::move(_Rhs.func_))
      , dismiss_(_Rhs.dismiss_) {
    _Rhs.dismiss();
  }

  ~ScopeGuard() {
    if (!dismiss_) func_();
  }

public: // modifiers
  void dismiss() { dismiss_ = true; }

  // NOTE: Call `dismiss()` manually to withdraw the function.

private:
  F    func_;
  bool dismiss_;
};

/**
 * Generate a ScopeGuard instance in try-catch with a function you use to
 * prevent leakage.
 *
 * @tparam F
 * @tparam R
 * @param f
 * @return
 */
template <typename F, typename R = ScopeGuard<typename std::decay<F>::type>>
R make_guard(F&& f) {
  return R(std::forward<F>(f));
}

} // namespace kata

#endif

/**
 * Copy constructor is implicitly deleted because has a user-declared
 * move constructor!
 */
