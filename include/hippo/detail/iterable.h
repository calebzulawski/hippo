#ifndef HIPPO_DETAIL_ITERABLE_H_
#define HIPPO_DETAIL_ITERABLE_H_

#include "base.h"
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>

namespace hippo {

namespace detail {
template <typename Container> struct container_base {

  static std::string suffix() { return "]"; }
  static std::vector<std::string> print(const Container &c,
                                        std::uint64_t indent,
                                        std::uint64_t current_indent) {
    std::vector<std::string> lines;
    using value_type = std::remove_cv_t<std::remove_reference_t<decltype(
        *std::cbegin(std::declval<Container>()))>>;
    if constexpr (::hippo::has_prefix_v<value_type>)
      current_indent += indent;
    for (const auto &e : c) {
      if constexpr (::hippo::has_stringifier<value_type>::value) {
        lines.emplace_back(
            std::string(current_indent, ' ')
                .append(::hippo::stringifier<value_type>::stringify(e)));
      } else {
        if constexpr (::hippo::has_prefix_v<value_type>)
          lines.emplace_back(
              std::string(current_indent, ' ')
                  .append(::hippo::printer<value_type>::prefix()));
        auto sublines = ::hippo::printer<value_type>::print(
            e, indent, current_indent + indent);
        lines.insert(lines.end(), sublines.begin(), sublines.end());
        if constexpr (::hippo::has_suffix_v<value_type>)
          lines.emplace_back(
              std::string(current_indent, ' ')
                  .append(::hippo::printer<value_type>::suffix()));
      }
    }
    return lines;
  }
};

} // namespace detail

template <typename... T>
struct printer<std::vector<T...>> : detail::container_base<std::vector<T...>> {
  static std::string prefix() { return "std::vector ["; }
};

template <typename... T>
struct printer<std::list<T...>> : detail::container_base<std::list<T...>> {
  static std::string prefix() { return "std::list ["; }
};

template <typename... T>
struct printer<std::forward_list<T...>>
    : detail::container_base<std::forward_list<T...>> {
  static std::string prefix() { return "std::forward_list ["; }
};

template <typename... T>
struct printer<std::deque<T...>> : detail::container_base<std::deque<T...>> {
  static std::string prefix() { return "std::deque ["; }
};

template <typename... T>
struct printer<std::set<T...>> : detail::container_base<std::set<T...>> {
  static std::string prefix() { return "std::set ["; }
};

template <typename... T>
struct printer<std::multiset<T...>>
    : detail::container_base<std::multiset<T...>> {
  static std::string prefix() { return "std::multiset ["; }
};

template <typename... T>
struct printer<std::unordered_set<T...>>
    : detail::container_base<std::unordered_set<T...>> {
  static std::string prefix() { return "std::unordered_set ["; }
};

template <typename... T>
struct printer<std::unordered_multiset<T...>>
    : detail::container_base<std::unordered_multiset<T...>> {
  static std::string prefix() { return "std::unordered_multiset ["; }
};

template <typename T, std::size_t N>
struct printer<std::array<T, N>> : detail::container_base<std::array<T, N>> {
  static std::string prefix() { return "std::array ["; }
};

template <typename T, std::size_t N>
struct printer<T[N]> : detail::container_base<T[N]> {
  static std::string prefix() { return "native array ["; }
};

} // namespace hippo

#endif // HIPPO_DETAIL_ITERABLE_H_
