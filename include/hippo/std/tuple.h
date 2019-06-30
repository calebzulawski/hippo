#ifndef HIPPO_STD_TUPLE_H_
#define HIPPO_STD_TUPLE_H_

#include "../hippo.h"
#include <tuple>

namespace hippo {

namespace detail {
template <typename Tuple, typename Format, std::size_t... I>
::hippo::object tuple_print_impl(const Tuple &t, std::uint64_t current_indent,
                                 const ::hippo::configuration &config,
                                 const Format &format,
                                 std::index_sequence<I...>) {
  std::list<::hippo::object> objects;
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                       "std::tuple {");
  (
      [&] {
        using printer_type = ::hippo::printer<std::remove_cv_t<
            std::remove_reference_t<decltype(std::get<I>(t))>>>;
        objects.push_back(
            printer_type::print(std::get<I>(t), current_indent + 1, config, std::get<I>(format.element_formats));
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

template <typename... T> struct tuple_format {
  std::tuple<::hippo::printer<T>::format_type...> element_formats;
};

template <typename... T> struct printer<std::tuple<T...>> {
  using format_type = tuple_format<T...>;
  static ::hippo::object print(const std::tuple<T...> &t,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format) {
    return detail::tuple_print_impl(t, current_indent, config, format,
                                    std::make_index_sequence<sizeof...(T)>{});
  }
};

} // namespace hippo

#endif // HIPPO_STD_TUPLE_H_
