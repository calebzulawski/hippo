#ifndef HIPPO_STD_UTILITY_H_
#define HIPPO_STD_UTILITY_H_

#include "../hippo.h"
#include <utility>

namespace hippo {

template <typename First, typename Second>
struct printer<std::pair<First, Second>> {
  static ::hippo::object print(const std::pair<First, Second> &p,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config) {
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "std::pair {");
    objects.push_back(
        printer<First>::print(p.first, current_indent + 1, config));
    std::visit(::hippo::prepend_visitor{"first: "}, objects.back());
    std::visit(::hippo::append_visitor{","}, objects.back());
    objects.push_back(
        printer<Second>::print(p.second, current_indent + 1, config));
    std::visit(::hippo::prepend_visitor{"second: "}, objects.back());
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "}");
    return ::hippo::condense(objects, config);
  }
};

}


#endif // HIPPO_STD_UTILITY_H_
