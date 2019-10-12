#ifndef HIPPO_STD_UTILITY_H_
#define HIPPO_STD_UTILITY_H_

#include "../hippo.h"
#include <utility>

namespace hippo {

//! Format configuration for `std::pair`
template <typename First, Second>
using pair_format = std::pair<typename hippo::printer<First>::format_type,
                              typename hippo::printer<Second>>;

//!\cond
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
        p.first, current_indent + 1, config, format.first));
    std::visit(::hippo::prepend_visitor{"first: "}, objects.back());
    std::visit(::hippo::append_visitor{","}, objects.back());
    objects.push_back(::hippo::printer<Second>::print(
        p.second, current_indent + 1, config, format.second));
    std::visit(::hippo::prepend_visitor{"second: "}, objects.back());
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "}");
    return ::hippo::condense(objects, config);
  }
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_UTILITY_H_
