#include <gtest/gtest.h>
#include <utils.h>

// Demonstrate some basic assertions.
TEST(UtilsTest, TestSum) {
  // Expect equality.
  EXPECT_EQ(utils::add2(20,22), 42);
}

TEST(UtilsTest, TestLog) {
  testing::internal::CaptureStdout();
  utils::log("My Test");
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ("My Test\n",output);
}

TEST(UtilsTest, TestErrorLog) {
  testing::internal::CaptureStdout();
  EXPECT_DEATH({utils::exitWithError("My Test");}, "");
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ("ERROR: My Test\n",output);
}