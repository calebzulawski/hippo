#ifndef HIPPO_STD_STRING_H_
#define HIPPO_STD_STRING_H_

#include "../hippo.h"
#include <list>
#include <sstream>
#include <string>

namespace hippo {

namespace detail {
inline ::hippo::object print_impl(const std::string &s,
                                  std::uint64_t current_indent,
                                  const ::hippo::configuration &config,
                                  const std::string &name) {
  std::list<std::string> lines;
  std::istringstream ss(s);
  std::string l;
  while (std::getline(ss, l))
    lines.emplace_back(l);
  if (lines.size() == 0) {
    return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                           name + " [empty]"};
  } else {
    std::list<::hippo::line> retlines;
    retlines.emplace_front(current_indent, name + " [");
    for (const auto &l : lines)
      retlines.emplace_back(current_indent + 1, l);
    retlines.emplace_back(current_indent, "]");
    return (lines.size() == 1)
               ? condense(retlines, config)
               : ::hippo::object{std::in_place_type<std::list<::hippo::line>>,
                                 retlines};
  }
}
} // namespace detail

template <> struct printer<std::string> {
  using format_type = ::hippo::no_format;
  static ::hippo::object print(const std::string &s,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type & = format_type()) {
    return detail::print_impl(s, current_indent, config, "std::string");
  }
};

template <> struct printer<const char *> {
  using format_type = ::hippo::no_format;
  static ::hippo::object print(const char *s, std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type & = format_type()) {
    return detail::print_impl(std::string(s), current_indent, config,
                              "char array");
  }
};

} // namespace hippo

#endif // HIPPO_STD_STRING_H_
