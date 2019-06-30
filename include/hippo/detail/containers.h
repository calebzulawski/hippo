#ifndef HIPPO_DETAIL_CONTAINERS_H_
#define HIPPO_DETAIL_CONTAINERS_H_

#include "base.h"
#include "formatter.h"

namespace hippo::detail {

template <typename Container, typename Base> struct arraylike_base {
  using printer_type = ::hippo::printer<std::remove_cv_t<
      std::remove_reference_t<decltype(*std::declval<Container>().begin())>>>;
  using format_type = typename printer_type::format_type;
  static ::hippo::object print(const Container &c, std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         Base::prefix);
    auto size = std::size(c);
    for (const auto &element : c) {
      objects.push_back(
          printer_type::print(element, current_indent + 1, config, format));
      if (--size != 0)
        std::visit(::hippo::append_visitor{","}, objects.back());
    }
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "]");
    return condense(objects, config);
  }
};

template <typename Container, typename Base> struct maplike_base {
  using printer_type =
      ::hippo::printer<std::remove_cv_t<std::remove_reference_t<decltype(
          std::declval<Container>().begin()->first)>>>;
  using format_type = typename printer_type::format_type;
  static ::hippo::object print(const Container &c, std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         Base::prefix);
    auto size = std::size(c);
    for (const auto &[key, value] : c) {
      std::list<::hippo::object> subobjects;
      subobjects.emplace_back(std::in_place_type<::hippo::line>,
                              current_indent + 1, "(");

      // key
      auto key_subobject =
          printer_type::print(key, current_indent + 2, config, format);
      std::visit(::hippo::prepend_visitor{"key :"}, key_subobject);
      std::visit(::hippo::append_visitor{","}, key_subobject);
      subobjects.push_back(key_subobject);

      // value
      auto value_subobject = ::hippo::printer<std::remove_cv_t<
          std::remove_reference_t<decltype(value)>>>::print(value,
                                                            current_indent + 2,
                                                            config);
      std::visit(::hippo::prepend_visitor{"value: "}, value_subobject);
      subobjects.push_back(value_subobject);

      // wrap up
      subobjects.emplace_back(std::in_place_type<::hippo::line>,
                              current_indent + 1, (--size == 0) ? ")" : "),");
      objects.push_back(condense(subobjects, config));
    }
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "]");
    return condense(objects, config);
  }
};

} // namespace hippo::detail

#endif // HIPPO_DETAIL_CONTAINERS_H_
