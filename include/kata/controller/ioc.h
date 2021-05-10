// Created by Jiaheng on 2021/5/10.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Inversion of Control.

#ifndef KATA_IOC_H
#define KATA_IOC_H

#include <kata/more_traits/function_traits.h>
#include <kata/noncopyable.h>

#include <any>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace kata {

//

class Ioc : public Noncopyable {
  std::unordered_map<std::string, std::any> m_creators;

 public:
  template <class TA, typename TB, typename... Args>
  auto RegisterType(const std::string& key)
      -> std::enable_if_t<!std::is_base_of<TA, TB>::value, void> {
    // ban duplicated keys
    if (m_creators.find(key) != m_creators.end())
      throw std::invalid_argument("");

    // register constructor into dictionary
    m_creators.emplace(
        key, to_function([](Args... args) { return new TA(new TB(args...)); }));
  }

  template <class T, typename... Args>
  T* Resolve(const std::string& key, Args... args) {
    return m_creators.find(key) == m_creators.end()
               ? nullptr
               : std::any_cast<std::function<T*(Args...)>>(
                     std::any(m_creators[key]))(args...);
  }

  template <class T, typename... Args>
  std::shared_ptr<T> ResolveShared(const std::string& key, Args... args) {
    return std::shared_ptr<T>(Resolve<T>(key, args...));
  }
};

}  // namespace kata

#endif  // KATA_IOC_H
