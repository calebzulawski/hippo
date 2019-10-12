#ifndef HIPPO_STD_COMPLEX_H_
#define HIPPO_STD_COMPLEX_H_

#include "../formatting/float.h"
#include "../formatting/integer.h"
#include "../hippo.h"
#include <complex>
#include <type_traits>

namespace hippo {

// technically not supported by the standard, but many implementations allow
// integer complex types
//!\cond
template <typename T>
struct printer<std::complex<T>, std::enable_if_t<std::is_integral_v<T> &&
                                                     !std::is_same_v<T, bool>,
                                                 std::complex<T>>> {
  using format_type = ::hippo::integer_format;
  static ::hippo::object print(const std::complex<T> &t,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &,
                               const format_type &format = format_type()) {
    return ::hippo::object{
        std::in_place_type<::hippo::line>, current_indent,
        ::hippo::apply_format(t.real(), format) +
            (t.imag() > 0 ? " + " : " - ") +
            ::hippo::apply_format(std::abs(t.imag()), format) + "i"};
  }
};

template <typename T>
struct printer<std::complex<T>,
               std::enable_if_t<std::is_floating_point_v<T>, std::complex<T>>> {
  using format_type = ::hippo::float_format;
  static ::hippo::object print(const std::complex<T> &t,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &,
                               const format_type &format = format_type()) {
    return ::hippo::object{
        std::in_place_type<::hippo::line>, current_indent,
        ::hippo::apply_format(t.real(), format) +
            (t.imag() > 0 ? " + " : " - ") +
            ::hippo::apply_format(std::abs(t.imag()), format) + "i"};
  }
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_COMPLEX_H_
