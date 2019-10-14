#ifndef HIPPO_STD_TUPLE_H_
#define HIPPO_STD_TUPLE_H_

#include "../hippo.h"
#include <tuple>

namespace hippo {

namespace detail {
template <typename Tuple, typename Format, std::size_t... I>
::hippo::object tuple_print_impl(const Tuple &t, std::uint64_t current_indent,
                                 const ::hippo::configuration &config,
                                 const Format &formats,
                                 std::index_sequence<I...>) {
  std::list<::hippo::object> objects;
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                       "std::tuple {");
  auto print = [&](auto index, auto val, auto fmt) {
    using printer_type = ::hippo::printer<
        std::remove_cv_t<std::remove_reference_t<decltype(val)>>>;
    objects.push_back(
        printer_type::print(val, current_indent + 1, config, fmt));
    std::visit(::hippo::prepend_visitor{std::to_string(index) + ": "},
               objects.back());
    if (index < sizeof...(I) - 1)
      std::visit(::hippo::append_visitor{","}, objects.back());
  };
  (print(I, std::get<I>(t), std::get<I>(formats)), ...);
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent, "}");
  return ::hippo::condense(objects, config);
}
} // namespace detail

//! Format for `std::tuple`
template <typename... T>
using tuple_format = std::tuple<typename ::hippo::printer<T>::format_type...>;

//!\cond
template <typename... T> struct printer<std::tuple<T...>> {
  using format_type = tuple_format<T...>;
  static ::hippo::object print(const std::tuple<T...> &t,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    return detail::tuple_print_impl(t, current_indent, config, format,
                                    std::make_index_sequence<sizeof...(T)>{});
  }
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_TUPLE_H_
