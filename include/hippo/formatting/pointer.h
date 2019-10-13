#ifndef HIPPO_FORMATTING_POINTER_H_
#define HIPPO_FORMATTING_POINTER_H_

#include "../detail/base.h"
#include <memory>
#include <optional>
#include <sstream>
#include <type_traits>
#include <variant>
#include <vector>

namespace hippo {

//! Abstract base for printers of polymorphic pointers
template <typename Base> struct base_type_printer {
  //! Prints `b` if possible, otherwise the return value is empty
  virtual std::optional<::hippo::object>
  print(const Base *b, std::uint64_t current_indent,
        const ::hippo::configuration &config) = 0;

  virtual ~base_type_printer() = default;
};

//! Printer for a polymorphic type from a base class pointer
template <typename Base, typename Derived>
struct derived_type_printer : base_type_printer<Base> {
  using printer_type =
      ::hippo::printer<Derived>; //!< Printer specialization for `Derived`
  using format_type =
      typename printer_type::format_type; //!< Format type of `Derived`

  //! Construct a printer using the default format
  derived_type_printer() = default;

  //! Construct a printer using the specified format `format`
  derived_type_printer(const format_type &format) : format(format) {}

  //! Prints `b` if it is a `Derived`, otherwise returns nothing
  std::optional<::hippo::object>
  print(const Base *b, std::uint64_t current_indent,
        const ::hippo::configuration &config) override {
    if (auto d = dynamic_cast<const Derived *>(b))
      return printer_type::print(*d, current_indent, config, format);
    else
      return std::nullopt;
  }

private:
  format_type format;
};

//! Format option for printing polymorphic types. A non-null pointer is checked
//! against the registered types, dereferenced, and printed.
template <typename T> struct dynamic_type_format {
  using base_format_type =
      typename ::hippo::printer<T>::format_type; //!< Format type of the base
                                                 //!< class
  std::vector<std::shared_ptr<base_type_printer<T>>>
      printers; //!< Printers for derived types, in preference order. Printers
                //!< are called one by one and returns the first successful
                //!< output.
  base_format_type base_format =
      base_format_type(); //!< If none of the derived printers are successful,
                          //!< the base class is printed with this format.
};

//! Format option for non-polymorphic pointers. A non-null pointer is
//! dereferenced and printed.
template <typename T> struct standard_pointer_format {
  using format_type =
      typename ::hippo::printer<T>::format_type; //!< Format type of `T`
  format_type format = format_type(); //!< The format used for printing
};

//! Format option for printing pointers as addresses (rather than printing the
//! dereferenced pointer)
struct address_format {};

//! Format for printing a pointer
template <typename T>
using pointer_format = std::variant<standard_pointer_format<T>, address_format,
                                    dynamic_type_format<T>>;

//! Apply format `fmt` to pointer `value` using the `current_indent` indentation
//! level and configuration `config`.
template <typename T>
::hippo::object apply_format(const T *value, std::uint64_t current_indent,
                             const ::hippo::configuration &config,
                             const pointer_format<T> &fmt) {
  if (!value)
    return ::hippo::line(current_indent, "nullptr");
  return std::visit(
      [&](const auto &fmt_alternative) -> ::hippo::object {
        using ArgType = std::decay_t<decltype(fmt_alternative)>;
        if constexpr (std::is_same_v<ArgType, standard_pointer_format<T>>) {
          return ::hippo::printer<T>::print(*value, current_indent, config,
                                            fmt_alternative.format);
        } else if constexpr (std::is_same_v<ArgType, address_format>) {
          std::ostringstream ss;
          ss << value;
          return ::hippo::line(current_indent, ss.str());
        } else if constexpr (std::is_same_v<ArgType, dynamic_type_format<T>>) {
          for (const auto &printer : fmt_alternative.printers) {
            if (auto lines = printer->print(value, current_indent, config))
              return *lines;
          }
          return ::hippo::printer<T>::print(*value, current_indent, config,
                                            fmt_alternative.base_format);
        }
      },
      fmt);
}

} // namespace hippo

#endif // HIPPO_FORMATTING_POINTER_H_
