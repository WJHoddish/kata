/**
 * Utilities.
 */

#include <gtest/gtest.h>

#include "experimental/any.h"
#include "utils/scope_guard.h"

TEST(utils, any) {
  using namespace kata;

  Any a(9);
  std::cout << any_cast<int>(a) << std::endl;

  a = 3.141;
  std::cout << any_cast<double>(a) << std::endl;
}

TEST(utils, scope_guard) {
  try {
    auto sg = kata::make_guard(
        [] { std::cout << "delete pointer(s) here" << std::endl; });

    // throw;

    // NOTE: Very last of this block, if no error, do not release resources.

    sg.dismiss();

  } catch (...) {
    // automatically call registered function here as object destruction
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}