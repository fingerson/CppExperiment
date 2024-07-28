#include <gtest/gtest.h>
#include <local_tcp_server.h>
#include <local_tcp_server.cpp>

// Demonstrate some basic assertions.
TEST(TcpServerTest, TestSum) {
  // Expect equality.
  EXPECT_EQ(add2(20,22), 42);
}