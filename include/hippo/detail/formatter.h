#ifndef HIPPO_DETAIL_FORMATTER_H_
#define HIPPO_DETAIL_FORMATTER_H_

#include "base.h"
#include <type_traits>
#include <utility>

namespace hippo {

//! Format for non-formattable types
struct no_format {};

//! A printable type that applies formats to other printable types
template <typename T> struct formatter {
  using value_type = std::remove_const_t<T>;         //!< The type to format
  using printer_type = ::hippo::printer<value_type>; //!< The printer for `T`
  using format_type =
      typename printer_type::format_type; //!< The format configuration for `T`

  formatter() = delete;
  formatter(const formatter &) = delete;
  formatter(formatter &&) = delete;

  //! Construct a `formatter` that prints `value` with the format described by
  //! `format`.
  //! The constructed `formatter` does not own `value` or `format`, so both must
  //! remain in scope for the lifetime of the `formatter`.
  formatter(const value_type &value, const format_type &format)
      : value(value), format(format) {}

  friend struct ::hippo::printer<formatter>;

private:
  const value_type &value;
  const format_type &format;
};

//! Specialization of `formatter` for pointer types
template <typename T> struct formatter<T *> {
  using value_type =
      std::remove_const_t<std::decay_t<T>>;            //!< The type to format
  using printer_type = ::hippo::printer<value_type *>; //!< The printer for `T`
  using format_type =
      typename printer_type::format_type; //!< The format configuration for `T`

  formatter() = delete;
  formatter(const formatter &) = delete;
  formatter(formatter &&) = delete;

  //! Construct a `formatter` that prints `value` with the format described by
  //! `format`.
  //! The constructed `formatter` does not own `value` or `format`, so both must
  //! remain in scope for the lifetime of the `formatter`.
  formatter(const value_type *value, const format_type &format)
      : value(value), format(format) {}

  friend struct ::hippo::printer<formatter>;

private:
  const value_type *value;
  const format_type &format;
};

//! Deduction guide for constructing a `formatter`
template <typename T>
formatter(const T &, const typename formatter<T>::format_type &)->formatter<T>;

//!\cond
template <typename T> struct printer<formatter<T>> {
  using format_type = ::hippo::no_format;
  static ::hippo::object print(const formatter<T> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type & = format_type()) {
    return formatter<T>::printer_type::print(o.value, current_indent, config,
                                             o.format);
  }
};
//!\endcond

} // namespace hippo

#endif // HIPPO_DETAIL_FORMATTER_H_
