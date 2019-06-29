#ifndef HIPPO_DETAIL_CONTAINERS_H_
#define HIPPO_DETAIL_CONTAINERS_H_

#include "base.h"

namespace hippo::detail {

template <typename Container, typename Base> struct arraylike_base {
  static ::hippo::object print(const Container &c, std::uint64_t current_indent,
                               const ::hippo::configuration &config) {
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         Base::prefix);
    auto size = std::size(c);
    for (const auto &element : c) {
      objects.push_back(
          ::hippo::printer<std::remove_cv_t<std::remove_reference_t<decltype(
              element)>>>::print(element, current_indent + 1, config));
      if (--size != 0)
        std::visit(::hippo::append_visitor{","}, objects.back());
    }
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "]");
    return condense(objects, config);
  }
};

template <typename Container, typename Base> struct maplike_base {
  static ::hippo::object print(const Container &c, std::uint64_t current_indent,
                               const ::hippo::configuration &config) {
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         Base::prefix);
    auto size = std::size(c);
    for (const auto &[key, value] : c) {
      std::list<::hippo::object> subobjects;
      subobjects.emplace_back(std::in_place_type<::hippo::line>,
                              current_indent + 1, "(");

      // key
      auto key_subobject = ::hippo::printer<std::remove_cv_t<
          std::remove_reference_t<decltype(key)>>>::print(key,
                                                          current_indent + 2,
                                                          config);
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
