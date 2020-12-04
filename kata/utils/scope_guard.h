// Copyright (c) 2020/11/9 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//
// A garbage collector is triggered when an exception occurs in try blocks.

#ifndef KATA_SCOPE_GUARD_H
#define KATA_SCOPE_GUARD_H

#include <type_traits>
#include <utility>

namespace kata {
/**
 * @brief Keep a functor as member var.
 *
 * @tparam F The registered function.
 */
template <typename F>
class ScopeGuard {
  F    func_;
  bool dismiss_;

public:
  explicit ScopeGuard(const F& f)
      : func_(f)
      , dismiss_(false) {}

  explicit ScopeGuard(F&& f)
      : func_(std::move(f))
      , dismiss_(false) {}

  ScopeGuard(ScopeGuard&& rhs) noexcept
      : func_(std::move(rhs.func_))
      , dismiss_(rhs.dismiss_) {
    rhs.dismiss();
  }

  /**
   * @brief Call the registered function in destruction if an exception occurs.
   */
  ~ScopeGuard() {
    if (!dismiss_) func_();
  }

  /**
   * @brief Manually withdraw the registered function.
   */
  void dismiss() { dismiss_ = true; }
};

/**
 * @brief Generate a ScopeGuard instance in try-catch with a function you use to
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
