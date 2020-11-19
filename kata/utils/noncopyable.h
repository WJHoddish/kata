// Copyright (c) 2020/11/6 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_NONCOPYABLE_H
#define KATA_NONCOPYABLE_H

namespace kata {
class NonCopyable {
protected:
  NonCopyable()                   = default;
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
};

} // namespace kata

#endif
