// Copyright (c) 2020/11/10 Jiaheng
// Author: Jiaheng <wjhgeneral@outlook.com>
//

#include "kata_all.h"
#include <gtest/gtest.h>

TEST(pattern, slot_pool) {
  kata::SlotPool<int>::get();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}