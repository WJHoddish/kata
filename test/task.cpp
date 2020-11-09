/**
 * Try C++ multi-thread.
 */

#include "task/message_bus.h"
#include "task/thread_pool.h"
#include "utils/scope_guard.h"
#include <gtest/gtest.h>

TEST(task, thread_pool) {
}

TEST(task, message_bus) {
}

TEST(task, scope_guard) {
  try {
    std::function<void()> f = [] {
      std::cout << "cleanup from abnormal exit" << std::endl;
    };

    auto gd = kata::make_guard(f);

    gd.dismiss();
  } catch (...) {
    // f will be automatically called in this block
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}