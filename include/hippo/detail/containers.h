#ifndef HIPPO_DETAIL_CONTAINERS_H_
#define HIPPO_DETAIL_CONTAINERS_H_

#include "base.h"
#include "formatter.h"
#include <utility>

namespace hippo {

//! Format for map types
template <typename Key, typename Value>
using map_format = std::pair<typename ::hippo::printer<Key>::format_type,
                             typename ::hippo::printer<Value>::format_type>;

namespace detail {

template <typename Container, typename Base> struct arraylike_base {
  using printer_type = ::hippo::printer<std::remove_cv_t<
      std::remove_reference_t<decltype(*std::declval<Container>().begin())>>>;
  using format_type = typename printer_type::format_type;
  static ::hippo::object print(const Container &c, std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    std::list<::hippo::object> objects;
    if (c.empty()) {
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           std::string(Base::prefix) + " [empty]");
    } else {
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           std::string(Base::prefix) + " [");
      if (c.begin() != c.end()) {
        objects.push_back(printer_type::print(*c.begin(), current_indent + 1,
                                              config, format));
        auto end = c.end();
        for (auto it = std::next(c.begin()); it != end; ++it) {
          std::visit(::hippo::append_visitor{","}, objects.back());
          objects.push_back(
              printer_type::print(*it, current_indent + 1, config, format));
        }
      }
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "]");
    }
    return condense(objects, config);
  }
};

template <typename Container, typename Base> struct maplike_base {
  using format_type =
      map_format<decltype(std::declval<Container>().begin()->first),
                 decltype(std::declval<Container>().begin()->second)>;
  static ::hippo::object print(const Container &c, std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    std::list<::hippo::object> objects;
    if (c.empty()) {
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           std::string(Base::prefix) + " [empty]");
    } else {
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           std::string(Base::prefix) + " [");
      auto size = std::size(c);
      for (const auto &[key, value] : c) {
        std::list<::hippo::object> subobjects;
        subobjects.emplace_back(std::in_place_type<::hippo::line>,
                                current_indent + 1, "(");

        // key
        auto key_subobject = ::hippo::printer<std::remove_cv_t<
            std::remove_reference_t<decltype(key)>>>::print(key,
                                                            current_indent + 2,
                                                            config,
                                                            format.first);
        std::visit(::hippo::prepend_visitor{"key: "}, key_subobject);
        std::visit(::hippo::append_visitor{","}, key_subobject);
        subobjects.push_back(key_subobject);

        // value
        auto value_subobject = ::hippo::printer<std::remove_cv_t<
            std::remove_reference_t<decltype(value)>>>::print(value,
                                                              current_indent +
                                                                  2,
                                                              config,
                                                              format.second);
        std::visit(::hippo::prepend_visitor{"value: "}, value_subobject);
        subobjects.push_back(value_subobject);

        // wrap up
        subobjects.emplace_back(std::in_place_type<::hippo::line>,
                                current_indent + 1, (--size == 0) ? ")" : "),");
        objects.push_back(condense(subobjects, config));
      }
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "]");
    }
    return condense(objects, config);
  }
};

} // namespace detail
} // namespace hippo

#endif // HIPPO_DETAIL_CONTAINERS_H_
