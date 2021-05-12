// Created by Jiaheng on 2021/5/10.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//
// Inversion of Control (IoC), the programming principle.

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

  template <class T, typename... Args>
  T* Resolve(const std::string& key, Args... args) {
    return m_creators.find(key) == m_creators.end()
               ? nullptr
               : std::any_cast<std::function<T*(Args...)>>(
                     std::any(m_creators[key]))(args...);
  }

 public:
  /**
   * Types should not have derived relation.
   * @tparam TA
   * @tparam TB
   * @tparam Args
   * @param key
   * @return
   */
  template <class TA, typename TB, typename... Args>
  auto RegisterType(const std::string& key)
      -> std::enable_if_t<!std::is_base_of<TA, TB>::value &&
                          !std::is_base_of<TB, TA>::value> {
    // ban duplicated keys
    if (m_creators.find(key) != m_creators.end()) throw;

    // register constructor into dictionary
    m_creators.emplace(
        key, to_function([](Args... args) { return new TA(new TB(args...)); }));
  }

  /**
   * Get an instance.
   * @tparam T
   * @tparam Args
   * @param key
   * @param args
   * @return
   */
  template <class T, typename... Args>
  auto ResolveShared(const std::string& key, Args... args) {
    return std::shared_ptr<T>(Resolve<T>(key, args...));
  }
};

}  // namespace kata

#endif  // KATA_IOC_H
