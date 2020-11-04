/**
 * Test C++ traits (template meta-programming).
 */

#include <gtest/gtest.h>
#include <more_traits.h>

class A {};

class B {};

class C {};

class AA : public A {};

TEST(more_traits, is_all_same) {
  EXPECT_EQ((kata::is_all_same<A, A, A>::value), true);

  EXPECT_EQ((kata::is_all_same<A, B, A>::value), false);

  EXPECT_EQ((kata::is_all_same<A, AA>::value), false);

  // NOTE: Define a var using the unified type, otherwise, compilation error.

  EXPECT_EQ((kata::is_all_same<int, int>::type(0)), 0);
}

TEST(more_traits, is_contained) {
  EXPECT_EQ((kata::is_contained<int, A, B, C, double>::value), false);
}

TEST(more_traits, type_count) {
  EXPECT_EQ((kata::type_count<int, int>::value), 2);
}

TEST(more_traits, at) {
  EXPECT_EQ(
      (std::is_same<kata::at<2, char, short, int, long>::type, int>::value),
      true);
}

TEST(more_traits, switch_case) {
  using namespace kata;

  EXPECT_EQ(
      (std::is_same<
          typename switch_<3 /*switch()*/, case_<1, A,            /*case 1:*/
                                                 case_<2, B,      /*case 2:*/
                                                       case_<3, C /*case 3:*/
                                                             >>>>::type,
          C>::value),
      true);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
