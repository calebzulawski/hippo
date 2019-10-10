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

template <typename Base> struct base_type_printer {
  virtual std::optional<::hippo::object>
  print(const Base *, std::uint64_t, const ::hippo::configuration &) = 0;

  virtual ~base_type_printer() = default;
};

template <typename Base, typename Derived>
struct derived_type_printer : base_type_printer<Base> {
  using printer_type = ::hippo::printer<Derived>;
  using format_type = typename printer_type::format_type;

  derived_type_printer() = default;
  derived_type_printer(const format_type &format) : format(format) {}

  std::optional<::hippo::object> print(const Base *b,
                                       std::uint64_t current_indent,
                                       const ::hippo::configuration &config) {
    if (auto d = dynamic_cast<const Derived *>(b))
      return printer_type::print(*d, current_indent, config, format);
    else
      return std::nullopt;
  }

private:
  format_type format;
};

template <typename T> struct dynamic_type_format {
  using base_format_type = typename ::hippo::printer<T>::format_type;
  std::vector<std::shared_ptr<base_type_printer<T>>> printers;
  base_format_type base_format = base_format_type();
};

template <typename T> struct standard_pointer_format {
  using format_type = typename ::hippo::printer<T>::format_type;
  format_type format = format_type();
};

struct address_format {};

template <typename T>
using pointer_format = std::variant<standard_pointer_format<T>, address_format,
                                    dynamic_type_format<T>>;

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
