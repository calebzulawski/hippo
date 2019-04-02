#ifndef HIPPO_DETAIL_STRING_H_
#define HIPPO_DETAIL_STRING_H_

#include "base.h"
#include <list>
#include <sstream>
#include <string>

namespace hippo {

namespace detail {
inline ::hippo::object print_impl(const std::string &s,
                                  std::uint64_t current_indent,
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
    return ::hippo::object{std::in_place_type<std::list<::hippo::line>>,
                           retlines};
  }
}
} // namespace detail

template <> struct printer<std::string> {
  static ::hippo::object print(const std::string &s,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &) {
    return detail::print_impl(s, current_indent, "std::string");
  }
};

template <> struct printer<const char *> {
  static ::hippo::object print(const char *s, std::uint64_t current_indent,
                               const ::hippo::configuration &) {
    return detail::print_impl(std::string(s), current_indent, "char array");
  }
};

} // namespace hippo

#endif // HIPPO_DETAIL_STRING_H_
