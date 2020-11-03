/**
 *
 */

#include <gtest/gtest.h>
#include <pmath.h>

TEST(test, test) { std::cout << "hello, world" << std::endl; }

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
