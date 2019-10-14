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
  auto print_if = [&](auto val, auto fmt) {
    using printer_type = ::hippo::printer<
        std::remove_cv_t<std::remove_reference_t<decltype(*val)>>>;
    if (val)
      objects.push_back(
          printer_type::print(*val, current_indent + 1, config, fmt));
  };
  (print_if(std::get_if<I>(&v), std::get<I>(format)), ...);
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent, "]");
  return ::hippo::condense(objects, config);
}
} // namespace detail

template <typename... T>
using variant_format = std::tuple<typename ::hippo::printer<T>::format_type...>;

//!\cond
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
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_VARIANT_H_
