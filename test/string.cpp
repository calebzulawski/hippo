#include "catch.hpp"
#include "hippo/hippo.h"

TEST_CASE("string") {
  hippo::configuration config;
  config.indent = 2;
  SECTION("empty") {
    std::string s;
    std::vector<std::string> expected_string{{"std::string [empty]"}};
    std::vector<std::string> expected_cstr{{"char array [empty]"}};
    SECTION("expanded") {
      config.width = 0;
      REQUIRE(hippo::print(s, config) == expected_string);
      REQUIRE(hippo::print(s.c_str(), config) == expected_cstr);
    }
    SECTION("condensed") {
      config.width = 100;
      REQUIRE(hippo::print(s, config) == expected_string);
      REQUIRE(hippo::print(s.c_str(), config) == expected_cstr);
    }
  }
  SECTION("single line") {
    std::string s("line");
    SECTION("expanded") {
      config.width = 0;
      std::vector<std::string> expected_string{
          {"std::string [", "  line", "]"}};
      std::vector<std::string> expected_cstr{{"char array [", "  line", "]"}};
      REQUIRE(hippo::print(s, config) == expected_string);
      REQUIRE(hippo::print(s.c_str(), config) == expected_cstr);
    }
    SECTION("condensed") {
      config.width = 100;
      std::vector<std::string> expected_string{{"std::string [ line ]"}};
      std::vector<std::string> expected_cstr{{"char array [ line ]"}};
      REQUIRE(hippo::print(s, config) == expected_string);
      REQUIRE(hippo::print(s.c_str(), config) == expected_cstr);
    }
  }
  SECTION("multiline") {
    std::string s("line 1\nline 2");
    std::vector<std::string> expected_string{
        {"std::string [", "  line 1", "  line 2", "]"}};
    std::vector<std::string> expected_cstr{
        {"char array [", "  line 1", "  line 2", "]"}};
    SECTION("expanded") {
      config.width = 0;
      REQUIRE(hippo::print(s, config) == expected_string);
      REQUIRE(hippo::print(s.c_str(), config) == expected_cstr);
    }
    SECTION("condensed") {
      config.width = 100;
      REQUIRE(hippo::print(s, config) == expected_string);
      REQUIRE(hippo::print(s.c_str(), config) == expected_cstr);
    }
  }
}
