// Created by Jiaheng on 2021/5/4.
// Copyright (c) 2021 Jiaheng Wang All rights reserved.
//

template <typename... Args>
void print(Args... args) {
  std::initializer_list<int>{(std::cout << args << '\t', 1)...};
  std::cout << '\n';
}
