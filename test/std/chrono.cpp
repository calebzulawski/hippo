#include "hippo/std/chrono.h"
#include "catch.hpp"

#define HELPER(Type, Unit)                                                     \
  SECTION(Unit) {                                                              \
    Type d{100};                                                               \
    SECTION("expanded") {                                                      \
      config.width = 0;                                                        \
      std::vector<std::string> expected_string{                                \
          {"std::chrono::duration containing [", "  100 " Unit, "]"}};         \
      REQUIRE(hippo::print(d, config) == expected_string);                     \
    }                                                                          \
    SECTION("condensed") {                                                     \
      config.width = 100;                                                      \
      std::vector<std::string> expected_string{                                \
          {"std::chrono::duration containing [ 100 " Unit " ]"}};              \
      REQUIRE(hippo::print(d, config) == expected_string);                     \
    }                                                                          \
    SECTION("formatted") {                                                     \
      config.width = 100;                                                      \
      hippo::integer_format fmt;                                               \
      fmt.base = hippo::integer_format::base_type::hex;                        \
      std::vector<std::string> expected_string{                                \
          {"std::chrono::duration containing [ 0x64 " Unit " ]"}};             \
      REQUIRE(hippo::print(hippo::formatter(d, fmt), config) ==                \
              expected_string);                                                \
    }                                                                          \
  }

#define HELPER_FLOAT(Type, Unit)                                               \
  SECTION(Unit) {                                                              \
    Type d{123.4};                                                             \
    SECTION("expanded") {                                                      \
      config.width = 0;                                                        \
      std::vector<std::string> expected_string{                                \
          {"std::chrono::duration containing [", "  123.4 " Unit, "]"}};       \
      REQUIRE(hippo::print(d, config) == expected_string);                     \
    }                                                                          \
    SECTION("condensed") {                                                     \
      config.width = 100;                                                      \
      std::vector<std::string> expected_string{                                \
          {"std::chrono::duration containing [ 123.4 " Unit " ]"}};            \
      REQUIRE(hippo::print(d, config) == expected_string);                     \
    }                                                                          \
    SECTION("format") {                                                        \
      config.width = 100;                                                      \
      hippo::float_format fmt;                                                 \
      fmt.format = hippo::float_format::format_type::scientific;               \
      fmt.precision = 1;                                                       \
      std::vector<std::string> expected_string{                                \
          {"std::chrono::duration containing [ 1.2e+02 " Unit " ]"}};          \
      REQUIRE(hippo::print(hippo::formatter(d, fmt), config) ==                \
              expected_string);                                                \
    }                                                                          \
  }

TEST_CASE("duration") {
  hippo::configuration config;
  config.indent = 2;
  SECTION("integer") {
    HELPER(std::chrono::nanoseconds, "nanoseconds");
    HELPER(std::chrono::microseconds, "microseconds");
    HELPER(std::chrono::milliseconds, "milliseconds");
    HELPER(std::chrono::seconds, "seconds");
    HELPER(std::chrono::minutes, "minutes");
    HELPER(std::chrono::hours, "hours");
    using days = std::chrono::duration<int64_t, std::ratio<86400>>;
    using weeks = std::chrono::duration<int64_t, std::ratio<604800>>;
    using months = std::chrono::duration<int64_t, std::ratio<2629746>>;
    using years = std::chrono::duration<int64_t, std::ratio<31556952>>;
    using custom1 = std::chrono::duration<int64_t, std::ratio<15, 1>>;
    using custom2 = std::chrono::duration<int64_t, std::ratio<3, 17>>;
    HELPER(days, "days");
    HELPER(weeks, "weeks");
    HELPER(months, "months");
    HELPER(years, "years");
    HELPER(custom1, "15-seconds");
    HELPER(custom2, "(3/17)-seconds");
  }
  SECTION("double") {
    using nanoseconds = std::chrono::duration<double, std::nano>;
    using microseconds = std::chrono::duration<double, std::micro>;
    using milliseconds = std::chrono::duration<double, std::milli>;
    using seconds = std::chrono::duration<double, std::ratio<1>>;
    using minutes = std::chrono::duration<double, std::ratio<60>>;
    using hours = std::chrono::duration<double, std::ratio<3600>>;
    using days = std::chrono::duration<double, std::ratio<86400>>;
    using weeks = std::chrono::duration<double, std::ratio<604800>>;
    using months = std::chrono::duration<double, std::ratio<2629746>>;
    using years = std::chrono::duration<double, std::ratio<31556952>>;
    using custom1 = std::chrono::duration<double, std::ratio<15, 1>>;
    using custom2 = std::chrono::duration<double, std::ratio<3, 17>>;
    HELPER_FLOAT(nanoseconds, "nanoseconds");
    HELPER_FLOAT(microseconds, "microseconds");
    HELPER_FLOAT(milliseconds, "milliseconds");
    HELPER_FLOAT(seconds, "seconds");
    HELPER_FLOAT(minutes, "minutes");
    HELPER_FLOAT(hours, "hours");
    HELPER_FLOAT(days, "days");
    HELPER_FLOAT(weeks, "weeks");
    HELPER_FLOAT(months, "months");
    HELPER_FLOAT(years, "years");
    HELPER_FLOAT(custom1, "15-seconds");
    HELPER_FLOAT(custom2, "(3/17)-seconds");
  }
}
