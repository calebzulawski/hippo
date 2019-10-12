#ifndef HIPPO_FORMATTING_INTEGER_H_
#define HIPPO_FORMATTING_INTEGER_H_

#include <ios>
#include <sstream>
#include <type_traits>

namespace hippo {

//! Format for integer values
struct integer_format {
  //! Integer base description
  enum class base_type {
    oct, //!< Octal
    dec, //!< Decimal
    hex, //!< Hexadecimal
  };

  base_type base = base_type::dec; //<! Base format
};

//! Apply format `fmt` to integer `value`
template <typename T>
std::enable_if_t<std::is_integral_v<T>, std::string>
apply_format(T value, const integer_format &fmt) {
  std::ostringstream ss;
  switch (fmt.base) {
  case integer_format::base_type::oct:
    ss << std::oct << '0';
    break;
  case integer_format::base_type::dec:
    ss << std::dec;
    break;
  case integer_format::base_type::hex:
    ss << std::hex << "0x";
    break;
  }
  ss << value;
  return ss.str();
}

} // namespace hippo

#endif // HIPPO_FORMATTING_INTEGER_H_
