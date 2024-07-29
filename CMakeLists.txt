cmake_minimum_required(VERSION 3.14)
project(ExperimentsGoogle)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MAKE_PROGRAM /usr/bin/ninja)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)


SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

set(PROJECT_SOURCES 
  src/utils/utils.cpp
  src/xdo_interface/xdo_interface.cpp
)

set(PROJECT_HEADERS
  src/xdo_interface/
  src/utils
)

set(EXTERNAL_LIBRARIES
  Crow::Crow
  xdo
)

set(TEST_LIBRARIES
  GTest::gtest
  GTest::gtest_main
  GTest::gmock_main
)

set(TEST_SOURCES
  tests/basic_test.cc
  tests/utils/utils_test.cc
)

add_executable(Experiment
  src/main.cpp
  ${PROJECT_SOURCES}
)

find_package(Crow CONFIG REQUIRED)
target_link_libraries(Experiment
    PUBLIC
  ${EXTERNAL_LIBRARIES}
)

target_include_directories(Experiment
  PRIVATE
    ${PROJECT_HEADERS}
)

#target_compile_options(Experiment PRIVATE -lxdo)

enable_testing()

add_executable(basic_test
  ${PROJECT_SOURCES}
  ${TEST_SOURCES}
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(
  basic_test
  ${TEST_LIBRARIES}
  ${EXTERNAL_LIBRARIES}
)

target_include_directories(basic_test
  PRIVATE
    ${PROJECT_HEADERS}
)

#target_compile_options(basic_test PRIVATE -lxdo)

include(GoogleTest)
gtest_discover_tests(basic_test)