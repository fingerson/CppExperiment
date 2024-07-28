cmake_minimum_required(VERSION 3.14)
project(ExperimentsGoogle)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Experiment 
  src/main.cpp
  src/server_backend/local_tcp_server.cpp
)

target_include_directories(Experiment
  PRIVATE
    src/server_backend/
)

enable_testing()

add_executable(
  basic_test
  tests/basic_test.cc
  tests/server_backend/local_tcp_server_test.cc
)
target_link_libraries(
  basic_test
  GTest::gtest_main
)

target_include_directories(basic_test
  PRIVATE
    src/server_backend/
)

include(GoogleTest)
gtest_discover_tests(basic_test)