#ifndef HIPPO_STD_MEMORY_H_
#define HIPPO_STD_MEMORY_H_

#include "../hippo.h"
#include <memory>

namespace hippo {

//!\cond
template <typename T, typename Deleter>
struct printer<std::unique_ptr<T, Deleter>> {
  using value_type = std::remove_const_t<T>;
  using format_type = ::hippo::pointer_format<value_type>;
  static ::hippo::object print(const std::unique_ptr<T, Deleter> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    if (o) {
      std::list<::hippo::object> objects;
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "std::unique_ptr containing [");
      objects.push_back(
          ::hippo::apply_format(o.get(), current_indent + 1, config, format));
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "]");
      return ::hippo::condense(objects, config);
    } else {
      return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                             "std::unique_ptr [nullptr]"};
    }
  }
};

template <typename T> struct printer<std::shared_ptr<T>> {
  using value_type = std::remove_const_t<T>;
  using format_type = ::hippo::pointer_format<value_type>;
  static ::hippo::object print(const std::shared_ptr<T> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    if (o) {
      std::list<::hippo::object> objects;
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "std::shared_ptr containing [");
      objects.push_back(
          ::hippo::apply_format(o.get(), current_indent + 1, config, format));
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "]");
      return ::hippo::condense(objects, config);
    } else {
      return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                             "std::shared_ptr [nullptr]"};
    }
  }
};

template <typename T> struct printer<std::weak_ptr<T>> {
  using value_type = std::remove_const_t<T>;
  using format_type = ::hippo::pointer_format<value_type>;
  static ::hippo::object print(const std::weak_ptr<T> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    auto sptr = o.lock();
    if (sptr) {
      std::list<::hippo::object> objects;
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "std::weak_ptr containing [");
      objects.push_back(::hippo::apply_format(sptr.get(), current_indent + 1,
                                              config, format));
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "]");
      return ::hippo::condense(objects, config);
    } else {
      return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                             "std::weak_ptr [nullptr]"};
    }
  }
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_MEMORY_H_
