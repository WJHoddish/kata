/**
 * Test C++ traits (template meta-programming).
 */

#include <gtest/gtest.h>
#include <more_traits.h>

TEST(more_traits, ) { std::cout << "hello, world" << std::endl; }

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
