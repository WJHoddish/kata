// Copyright (c) 2020/11/9 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//
// Ensure a gc handler will be called when an exception occurs in try-catch.

#ifndef KATA_SCOPE_GUARD_H
#define KATA_SCOPE_GUARD_H

#include <type_traits>
#include <utility>

namespace kata {
/**
 *
 * @tparam F The register function, which is normally used for cleaning up (any
 * resource allocated in the try-catch statement).
 */
template <typename F>
class ScopeGuard {
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
   * Call the registered function in destructor if it meets an exception in
   * try-catch.
   */
  ~ScopeGuard() {
    if (!dismiss_) {
      func_();
    }
  }

  /**
   * If there is no exception, manually call this func so that the registered
   * function would not be executed.
   */
  void dismiss() { dismiss_ = true; }

private:
  F func_;

  bool dismiss_;
};

/**
 * Helper function: Generate a <ScopeGuard> instance in try-catch with a
 * function you use to delete all dangerous pointers.
 *
 * @tparam F
 * @tparam R
 * @param f It's normally a gc handler.
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
