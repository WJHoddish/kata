// Copyright (c) 2020/11/6 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#ifndef KATA_MESSAGE_BUS_H
#define KATA_MESSAGE_BUS_H

#include <map>

#include "../more_traits/function_traits.h"
#include "../utils/any.h"
#include "../utils/noncopyable.h"

namespace kata {
class MessageBus {
  template <typename F>
  void add(const std::string& topic, F&& f) {
    std::string msg_type(topic + typeid(F).name());

    map_.emplace(std::move(msg_type), //
                 std::forward<F>(f));
  }

  std::multimap<std::string, Any /*non-template*/> map_;

public:
};

} // namespace kata

#endif
