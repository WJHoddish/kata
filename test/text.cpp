/**
 * Test any component relates to string or character array.
 */

#include "pattern/slot_pool.h"
#include "text/line.h"
#include <gtest/gtest.h>

TEST(text, slot_pool) {
  kata::SlotPool<int>::get();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}