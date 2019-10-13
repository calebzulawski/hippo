//!\file
#ifndef HIPPO_FORMATTING_FLOAT_H_
#define HIPPO_FORMATTING_FLOAT_H_

#include <iomanip>
#include <ios>
#include <optional>
#include <sstream>
#include <type_traits>

namespace hippo {

//! Format for floating-point values
struct float_format {
  //! Notation format description
  enum class notation_type {
    standard,   //!< Format with `std::defaultfloat`
    fixed,      //!< Format with `std::fixed`
    scientific, //!< Format with `std::scientific`
  };

  notation_type notation =
      notation_type::standard; //!< Notation format, defaults to `standard`
  std::optional<std::size_t> precision; //!< Precision for `std::setprecision`
};

//! Apply format `fmt` to floating-point `value`
template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, std::string>
apply_format(T value, const float_format &fmt) {
  std::ostringstream ss;
  switch (fmt.notation) {
  case float_format::notation_type::standard:
    ss << std::defaultfloat;
    break;
  case float_format::notation_type::fixed:
    ss << std::fixed;
    break;
  case float_format::notation_type::scientific:
    ss << std::scientific;
    break;
  }
  if (fmt.precision)
    ss << std::setprecision(*fmt.precision);
  ss << value;
  return ss.str();
}

} // namespace hippo

#endif // HIPPO_FORMATTING_FLOAT_H_
