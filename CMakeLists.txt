cmake_minimum_required(VERSION 3.14)
project(ExperimentsGoogle)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include(/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(PROJECT_SOURCES 
  src/utils/utils.cpp
)

set(PROJECT_HEADERS
  src/server_backend/
  src/utils
)

set(TEST_SOURCES
  tests/basic_test.cc
  tests/utils/utils_test.cc
)



include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Experiment
  src/main.cpp
  ${PROJECT_SOURCES}
)

find_package(Crow CONFIG REQUIRED)
target_link_libraries(Experiment
    PUBLIC
  Crow::Crow
)

target_include_directories(Experiment
  PRIVATE
    ${PROJECT_HEADERS}
)

enable_testing()

add_executable(basic_test
  ${PROJECT_SOURCES}
  ${TEST_SOURCES}
)

target_link_libraries(
  basic_test
  GTest::gtest_main
  Crow::Crow
)

target_include_directories(basic_test
  PRIVATE
    ${PROJECT_HEADERS}
)

include(GoogleTest)
gtest_discover_tests(basic_test)