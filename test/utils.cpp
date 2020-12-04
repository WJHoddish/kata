/**
 * Utilities.
 */

#include <gtest/gtest.h>

#include "utils/scope_guard.h"

TEST(utils, scope_guard) {
  try {
    auto sg = kata::make_guard(
        [] { std::cout << "delete pointer(s) here" << std::endl; });

    // throw;

    // NOTE: Since no error, resources should not be released.

    sg.dismiss();

  } catch (...) {
    // automatically call registered function here as object destruction
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}