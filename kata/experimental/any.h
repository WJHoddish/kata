// Copyright (c) 2020 Jiaheng Wang
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef KATA_ANY_H
#define KATA_ANY_H

#include <memory>

// #define KATA_NO_CXX11_RVALUE_REFERENCES

namespace kata {
class Any {
  template <typename T>
  friend T any_cast(const Any&);

public: // structors
  Any()
      : ptr_(nullptr) {}

  template <typename T>
  explicit Any(const T& _Val)
      : ptr_(new PlaceHolder<
             typename std::remove_cv<typename std::decay<const T>::type>::type>(
            _Val)) {}

  Any(const Any& _Src)
      : ptr_(_Src.ptr_ ? _Src.ptr_->clone() : nullptr) {}

#ifndef KATA_NO_CXX11_RVALUE_REFERENCES
  Any(Any&& _Src) noexcept
      : ptr_(_Src.ptr_) {
    _Src.ptr_ = nullptr;
  }

  template <typename T>
  explicit Any(
      T&& _Val,
      typename std::enable_if<!std::is_same<T, Any&>::value, T>::type* = 0,
      typename std::enable_if<!std::is_const<T>::value>::type* = 0) noexcept
      : ptr_(new PlaceHolder<typename std::decay<T>::type>(
            static_cast<T&&>(_Val))) {}
#endif

  ~Any() { delete ptr_; }

public: // modifiers
  Any& swap(Any& _Rhs) {
    PlaceHolderBase* temp = ptr_;
    ptr_                  = _Rhs.ptr_;
    _Rhs.ptr_             = temp;
    return *this;
  }

#ifdef KATA_NO_CXX11_RVALUE_REFERENCES
  template <typename T>
  Any& operator=(const T& _Val) {
    Any(_Val).swap(*this);
    return *this;
  }

  Any& operator=(Any _Rhs) {
    _Rhs.swap(*this);
    return *this;
  }
#else
  Any& operator=(const Any& _Rhs) {
    Any(_Rhs).swap(*this);
    return *this;
  }

  Any& operator=(Any&& _Rhs) noexcept {
    _Rhs.swap(*this);
    Any().swap(_Rhs);
    return *this;
  }

  template <class T>
  Any& operator=(T&& _Val) {
    Any(static_cast<T&&>(_Val)).swap(*this);
    return *this;
  }
#endif

public: // queries
  bool empty() const { return !ptr_; }

  void clear() { Any().swap(*this); }

private:
  struct PlaceHolderBase {
    virtual ~PlaceHolderBase()                  = default;
    virtual const std::type_info& type() const  = 0;
    virtual PlaceHolderBase*      clone() const = 0;
  };

  template <typename T>
  struct PlaceHolder final : public PlaceHolderBase {
    explicit PlaceHolder(const T& _Val)
        : val_(_Val) {}

#ifndef KATA_NO_CXX11_RVALUE_REFERENCES
    explicit PlaceHolder(T&& _Val)
        : val_(static_cast<T&&>(_Val)) {}
#endif

    const std::type_info& type() const override { return typeid(T); }
    PlaceHolderBase* clone() const override { return new PlaceHolder(val_); }
    PlaceHolder&     operator=(const PlaceHolder&) = delete;

    T val_;
  };

  PlaceHolderBase* ptr_;
};

template <typename T>
T any_cast(const Any& _Ins) {
  if (_Ins.ptr_->type() != typeid(T)) throw;

  // cast using <T>
  return static_cast<Any::PlaceHolder<T>*>(_Ins.ptr_)->val_;
}

} // namespace kata

#endif // KATA_ANY_H
