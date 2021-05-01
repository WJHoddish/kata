// Created by Jiaheng on 2021/4/30.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_FLOOR_H
#define KATA_FLOOR_H

#include "is_finite.h"

namespace gem {

//

namespace type_check {

//

namespace compute {

//

template <typename T>
constexpr T floor(const T x, const T i) noexcept {
  return i - static_cast<T>(static_cast<int>(x < T(0) && x < i));
}

}  // namespace compute

template <typename T>
constexpr T floor(const T x) noexcept {
  return is_nan(x)
             ?
             /**
              *
              */
             std::numeric_limits<T>::quiet_NaN()
             : is_inf(x)
                   ?
                   /**
                    *
                    */
                   x
                   : abs(x) < std::numeric_limits<T>::epsilon() ?
                                                                /**
                                                                 *
                                                                 */
                         x
                                                                :
                                                                /**
                                                                 *
                                                                 */
                         compute::floor(x, T(static_cast<long long int>(x)));
}

}  // namespace type_check

//

template <typename T>
constexpr return_t<T> floor(const T x) noexcept {
  return type_check::floor(static_cast<return_t<T>>(x));
}

}  // namespace gem

#endif  // KATA_FLOOR_H
