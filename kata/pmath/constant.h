// Copyright (c) 2020/11/5 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_CONSTANT_H
#define KATA_CONSTANT_H

namespace kata {
/**
 * Cast <T> natural constant.
 *
 * @tparam T
 */
template <typename T>
constexpr T e = T(2.7182818284590452353);

template <typename T>
constexpr T pi = T(3.1415926535897932385);

} // namespace kata

#endif
