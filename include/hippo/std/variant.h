#ifndef HIPPO_STD_VARIANT_H_
#define HIPPO_STD_VARIANT_H_

#include "../hippo.h"
#include <tuple>
#include <type_traits>
#include <variant>

namespace hippo {

namespace detail {
template <typename Variant, typename Format, std::size_t... I>
::hippo::object
variant_print_impl(const Variant &v, std::uint64_t current_indent,
                   const ::hippo::configuration &config, const Format &format,
                   std::index_sequence<I...>) {
  std::list<::hippo::object> objects;
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                       "std::variant containing [");
  (
      [&] {
        using printer_type = ::hippo::printer<std::remove_cv_t<
            std::remove_reference_t<decltype(std::get<I>(v))>>>;
        if (v.index() == I)
          objects.push_back(
              printer_type::print(std::get<I>(v), current_indent + 1, config,
                                  std::get<I>(format.alternative_formats)));
      }(),
      ...);
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent, "]");
  return ::hippo::condense(objects, config);
}
} // namespace detail

template <typename... T> struct variant_format {
  std::tuple<typename ::hippo::printer<T>::format_type...> alternative_formats;
};

template <typename... T> struct printer<std::variant<T...>> {
  using format_type = variant_format<T...>;
  static ::hippo::object print(const std::variant<T...> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    if (o.valueless_by_exception())
      return ::hippo::line(current_indent, "std::variant [valueless]");
    else
      return detail::variant_print_impl(
          o, current_indent, config, format,
          std::make_index_sequence<sizeof...(T)>{});
  }
};

} // namespace hippo

#endif // HIPPO_STD_VARIANT_H_
