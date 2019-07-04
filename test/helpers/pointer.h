#ifndef TEST_HELPER_POINTER_H_
#define TEST_HELPER_POINTER_H_

#define NULLPTR_SECTIONS(Name)                                                 \
  SECTION("expanded") {                                                        \
    config.width = 0;                                                          \
    std::vector<std::string> expected_string{{Name " [nullptr]"}};             \
    REQUIRE(hippo::print(ptr, config) == expected_string);                     \
    REQUIRE(hippo::print(const_ptr, config) == expected_string);               \
  }                                                                            \
  SECTION("condensed") {                                                       \
    config.width = 100;                                                        \
    std::vector<std::string> expected_string{{Name " [nullptr]"}};             \
    REQUIRE(hippo::print(ptr, config) == expected_string);                     \
    REQUIRE(hippo::print(const_ptr, config) == expected_string);               \
  }

#define VALUE_SECTIONS(Name, Value)                                            \
  SECTION("expanded") {                                                        \
    config.width = 0;                                                          \
    std::vector<std::string> expected_string{                                  \
        {Name " containing [", "  " Value, "]"}};                              \
    REQUIRE(hippo::print(ptr, config) == expected_string);                     \
    REQUIRE(hippo::print(const_ptr, config) == expected_string);               \
  }                                                                            \
  SECTION("condensed") {                                                       \
    config.width = 100;                                                        \
    std::vector<std::string> expected_string{                                  \
        {Name " containing [ " Value " ]"}};                                   \
    REQUIRE(hippo::print(ptr, config) == expected_string);                     \
    REQUIRE(hippo::print(const_ptr, config) == expected_string);               \
  }

#define FORMATTED_SECTIONS(Name, Value)                                        \
  SECTION("expanded") {                                                        \
    config.width = 0;                                                          \
    std::vector<std::string> expected_string{                                  \
        {Name " containing [", "  " Value, "]"}};                              \
    REQUIRE(hippo::print(hippo::formatter(ptr, fmt), config) ==                \
            expected_string);                                                  \
    REQUIRE(hippo::print(hippo::formatter(const_ptr, fmt), config) ==          \
            expected_string);                                                  \
  }                                                                            \
  SECTION("condensed") {                                                       \
    config.width = 100;                                                        \
    std::vector<std::string> expected_string{                                  \
        {Name " containing [ " Value " ]"}};                                   \
    REQUIRE(hippo::print(hippo::formatter(ptr, fmt), config) ==                \
            expected_string);                                                  \
    REQUIRE(hippo::print(hippo::formatter(const_ptr, fmt), config) ==          \
            expected_string);                                                  \
  }

#endif // TEST_HELPER_POINTER_H_
