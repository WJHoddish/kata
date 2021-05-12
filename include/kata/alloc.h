// Created by Jiaheng on 2021/5/12.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_ALLOC_H
#define KATA_ALLOC_H

#include <memory>

namespace kata {

//

constexpr std::size_t kCacheLineSize = 64;

//

template <typename T>
struct AlignedAlloc {
  template <typename... Args>
  static T* malloc(Args&&... args) {
#if defined(__GNUC__)
    void* ptr = _aligned_malloc(sizeof(T), kCacheLineSize);
#endif
    return ptr ? new (ptr) T(std::forward<Args>(args)...)  // placement new
               : nullptr;
  }

  static void free(T* ptr) {
    if (ptr) {
      ptr->~T();  // call destructor explicitly
#if defined(__GNUC__)
      _aligned_free((void*)ptr);
#endif
    }
  }
};

//

template <typename T>
struct AlignedDeleter {
  void operator()(T* ptr) const { AlignedAlloc<T>::free(ptr); }
};

//

template <typename T>
using aligned_ptr_t = std::unique_ptr<T, AlignedDeleter<T>>;

template <typename T, typename... Args>
auto make_aligned(Args&&... args) {
  return aligned_ptr_t<T>(AlignedAlloc<T>::malloc(std::forward<Args>(args)...));
}

}  // namespace kata

#endif  // KATA_ALLOC_H
