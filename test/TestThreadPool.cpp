// Created by Jiaheng on 2021/4/28.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include "TestThreadPool.h"

void thread_set_promise(std::promise<int>& prom) {
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  prom.set_value(35);
}

TEST(TestThreadPool, promise_future) {
  std::promise<int> prom;
  std::future<int>  fu = prom.get_future();

  // start thread
  std::thread t(&thread_set_promise, std::ref(prom));

  std::cout << "before get()" << std::endl;
  fu.get();
  std::cout << "after get()" << std::endl;

  t.join();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
