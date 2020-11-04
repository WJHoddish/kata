/**
 * Test Pure-function math.
 */

#include <gtest/gtest.h>
#include <pmath.h>

TEST(pmath, abs) {
  EXPECT_EQ(kata::abs(0), 0);
  EXPECT_EQ(kata::abs(12), 12);
  EXPECT_EQ(kata::abs(-3.141), 3.141);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
