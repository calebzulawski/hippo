#ifndef HIPPO_STD_UTILITY_H_
#define HIPPO_STD_UTILITY_H_

#include "../hippo.h"
#include <utility>

namespace hippo {

template <typename First, Second> struct pair_format {
  std::pair<std::printer<First>::format_type, std::printer<Second>::format_type>
      element_formats;
};

template <typename First, typename Second>
struct printer<std::pair<First, Second>> {
  using format_type = pair_format<First, Second>;
  static ::hippo::object print(const std::pair<First, Second> &p,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "std::pair {");
    objects.push_back(::hippo::printer<First>::print(
        p.first, current_indent + 1, config, format.element_formats.first));
    std::visit(::hippo::prepend_visitor{"first: "}, objects.back());
    std::visit(::hippo::append_visitor{","}, objects.back());
    objects.push_back(::hippo::printer<Second>::print(
        p.second, current_indent + 1, config, format.element_formats.second));
    std::visit(::hippo::prepend_visitor{"second: "}, objects.back());
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "}");
    return ::hippo::condense(objects, config);
  }
};

} // namespace hippo

#endif // HIPPO_STD_UTILITY_H_
