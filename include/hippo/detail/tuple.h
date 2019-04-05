#ifndef HIPPO_DETAIL_TUPLE_H_
#define HIPPO_DETAIL_TUPLE_H_

#include "base.h"
#include <tuple>
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

namespace detail {
template <typename Tuple, std::size_t... I>
::hippo::object tuple_print_impl(const Tuple &t, std::uint64_t current_indent,
                                 const ::hippo::configuration &config,
                                 std::index_sequence<I...>) {
  std::list<::hippo::object> objects;
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                       "std::tuple {");
  (
      [&] {
        objects.push_back(
            ::hippo::print_type(std::get<I>(t), current_indent + 1, config));
        std::visit(::hippo::prepend_visitor{std::to_string(I) + ": "},
                   objects.back());
        if (I < sizeof...(I) - 1)
          std::visit(::hippo::append_visitor{","}, objects.back());
      }(),
      ...);
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent, "}");
  return ::hippo::condense(objects, config);
}

} // namespace detail

template <typename... T> struct printer<std::tuple<T...>> {
  static ::hippo::object print(const std::tuple<T...> &t,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config) {
    return detail::tuple_print_impl(t, current_indent, config,
                                    std::make_index_sequence<sizeof...(T)>{});
  }
};

} // namespace hippo

#endif // HIPPO_DETAIL_TUPLE_H_
