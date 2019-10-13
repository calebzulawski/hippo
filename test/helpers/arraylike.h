#ifndef TEST_HELPER_ARRAYLIKE_H_
#define TEST_HELPER_ARRAYLIKE_H_

#include "catch.hpp"

#define TEST_ARRAYLIKE(Test, Type)                                             \
  TEST_CASE(Test) {                                                            \
    hippo::configuration config;                                               \
    config.indent = 2;                                                         \
    Type val{0, 1, 2};                                                         \
    SECTION("expanded") {                                                      \
      config.width = 0;                                                        \
      std::vector<std::string> expected_string{#Type " [", "  0,", "  1,",     \
                                               "  2", "]"};                    \
      REQUIRE(hippo::print(val, config) == expected_string);                   \
    }                                                                          \
    SECTION("compressed") {                                                    \
      config.width = 100;                                                      \
      std::vector<std::string> expected_string{#Type " [ 0, 1, 2 ]"};          \
      REQUIRE(hippo::print(val, config) == expected_string);                   \
    }                                                                          \
    SECTION("formatted") {                                                     \
      config.width = 100;                                                      \
      hippo::integer_format fmt;                                               \
      fmt.base = hippo::integer_format::base_type::hex;                        \
      std::vector<std::string> expected_string{#Type " [ 0x0, 0x1, 0x2 ]"};    \
      REQUIRE(hippo::print(hippo::formatter(val, fmt), config) ==              \
              expected_string);                                                \
    }                                                                          \
  }

#endif // TEST_HELPER_ARRAYLIKE_H_
