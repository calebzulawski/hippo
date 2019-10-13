#include "hippo/std/unordered_set.h"
#include "catch.hpp"
#include "hippo/hippo.h"
#include <unordered_set>

TEST_CASE("unordered_set") {
  hippo::configuration config;
  config.indent = 2;
  std::unordered_set val{1};
  SECTION("empty") {
    val.clear();
    std::vector<std::string> expected_string{"std::unordered_set [empty]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("expanded") {
    config.width = 0;
    std::vector<std::string> expected_string{"std::unordered_set [", "  1",
                                             "]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("compressed") {
    config.width = 100;
    std::vector<std::string> expected_string{"std::unordered_set [ 1 ]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("formatted") {
    config.width = 100;
    hippo::integer_format fmt;
    fmt.base = hippo::integer_format::base_type::hex;
    std::vector<std::string> expected_string{"std::unordered_set [ 0x1 ]"};
    REQUIRE(hippo::print(hippo::formatter(val, fmt), config) ==
            expected_string);
  }
}

TEST_CASE("unordered_multiset") {
  hippo::configuration config;
  config.indent = 2;
  std::unordered_multiset<int> val{1, 1};
  SECTION("empty") {
    val.clear();
    std::vector<std::string> expected_string{"std::unordered_multiset [empty]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("expanded") {
    config.width = 0;
    std::vector<std::string> expected_string{"std::unordered_multiset [",
                                             "  1,", "  1", "]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("compressed") {
    config.width = 100;
    std::vector<std::string> expected_string{
        "std::unordered_multiset [ 1, 1 ]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("formatted") {
    config.width = 100;
    hippo::integer_format fmt;
    fmt.base = hippo::integer_format::base_type::hex;
    std::vector<std::string> expected_string{
        "std::unordered_multiset [ 0x1, 0x1 ]"};
    REQUIRE(hippo::print(hippo::formatter(val, fmt), config) ==
            expected_string);
  }
}
