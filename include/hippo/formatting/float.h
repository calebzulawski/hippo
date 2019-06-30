#ifndef HIPPO_FORMATTING_FLOAT_H_
#define HIPPO_FORMATTING_FLOAT_H_

#include <iomanip>
#include <ios>
#include <optional>
#include <sstream>
#include <type_traits>

namespace hippo {

struct float_format {
  enum class format_type {
    standard,
    fixed,
    scientific,
  };

  format_type format = format_type::standard;
  std::optional<std::size_t> precision;
};

namespace detail {
template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, std::string>
apply_format(T value, const float_format &fmt) {
  std::ostringstream ss;
  switch (fmt.format) {
  case float_format::format_type::standard:
    ss << std::defaultfloat;
    break;
  case float_format::format_type::fixed:
    ss << std::fixed;
    break;
  case float_format::format_type::scientific:
    ss << std::scientific;
    break;
  }
  if (fmt.precision)
    ss << std::setprecision(*fmt.precision);
  ss << value;
  return ss.str();
}
} // namespace detail

} // namespace hippo

#endif // HIPPO_FORMATTING_FLOAT_H_
