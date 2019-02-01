#ifndef HIPPO_DETAIL_CONTAINERS_H_
#define HIPPO_DETAIL_CONTAINERS_H_

#include "base.h"
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace hippo {

namespace detail {

template <typename Container, typename Base> struct arraylike_base {
  static std::list<::hippo::line> print(const Container &c,
                                        std::uint64_t current_indent,
                                        const ::hippo::configuration &config) {
    std::list<::hippo::line> lines;
    lines.emplace_back(current_indent, Base::prefix);
    auto size = std::size(c);
    for (const auto &element : c) {
      auto sublines = ::hippo::printer<std::decay_t<decltype(element)>>::print(
          element, current_indent + 1, config);
      if (--size != 0)
        sublines.back().string += ",";
      condense(sublines, config);
      lines.splice(lines.end(), sublines);
    }
    lines.emplace_back(current_indent, "]");
    return lines;
  }
};

template <typename Container, typename Base> struct maplike_base {
  static std::list<::hippo::line> print(const Container &c,
                                        std::uint64_t current_indent,
                                        const ::hippo::configuration &config) {
    std::list<::hippo::line> lines;
    lines.emplace_back(current_indent, Base::prefix);
    auto size = std::size(c);
    for (const auto &[key, value] : c) {
      std::list<::hippo::line> sublines;
      sublines.emplace_back(current_indent + 1, "(");

      // key
      auto key_sublines = ::hippo::printer<std::decay_t<decltype(key)>>::print(
          key, current_indent + 2, config);
      ::hippo::line key_front(current_indent + 2,
                              "key: " + key_sublines.front().string);
      key_sublines.pop_front();
      key_sublines.push_front(key_front);
      key_sublines.back().string += ',';
      condense(key_sublines, config);
      sublines.splice(sublines.end(), key_sublines);

      // value
      auto value_sublines =
          ::hippo::printer<std::decay_t<decltype(value)>>::print(
              value, current_indent + 2, config);
      ::hippo::line value_front(current_indent + 2,
                                "value: " + value_sublines.front().string);
      value_sublines.pop_front();
      value_sublines.push_front(value_front);
      condense(value_sublines, config);
      sublines.splice(sublines.end(), value_sublines);

      // wrap up
      sublines.emplace_back(current_indent + 1, (--size == 0) ? ")" : "),");
      condense(sublines, config);
      lines.splice(lines.end(), sublines);
    }
    lines.emplace_back(current_indent, "]");
    return lines;
  }
};

} // namespace detail

template <typename... T>
struct printer<std::vector<T...>>
    : detail::arraylike_base<std::vector<T...>, printer<std::vector<T...>>> {
  constexpr static const char *prefix = "std::vector [";
};

template <typename... T>
struct printer<std::list<T...>>
    : detail::arraylike_base<std::list<T...>, printer<std::list<T...>>> {
  constexpr static const char *prefix = "std::list [";
};

template <typename... T>
struct printer<std::forward_list<T...>>
    : detail::arraylike_base<std::forward_list<T...>,
                             printer<std::forward_list<T...>>> {
  constexpr static const char *prefix = "std::forward_list [";
};

template <typename... T>
struct printer<std::deque<T...>>
    : detail::arraylike_base<std::deque<T...>, printer<std::deque<T...>>> {
  constexpr static const char *prefix = "std::deque [";
};

template <typename... T>
struct printer<std::set<T...>>
    : detail::arraylike_base<std::set<T...>, printer<std::set<T...>>> {
  constexpr static const char *prefix = "std::set [";
};

template <typename... T>
struct printer<std::multiset<T...>>
    : detail::arraylike_base<std::multiset<T...>,
                             printer<std::multiset<T...>>> {
  constexpr static const char *prefix = "std::multiset [";
};

template <typename... T>
struct printer<std::unordered_set<T...>>
    : detail::arraylike_base<std::unordered_set<T...>,
                             printer<std::unordered_set<T...>>> {
  constexpr static const char *prefix = "std::unordered_set [";
};

template <typename... T>
struct printer<std::unordered_multiset<T...>>
    : detail::arraylike_base<std::unordered_multiset<T...>,
                             printer<std::unordered_multiset<T...>>> {
  constexpr static const char *prefix = "std::unordered_multiset [";
};

template <typename T, std::size_t N>
struct printer<std::array<T, N>>
    : detail::arraylike_base<std::array<T, N>, printer<std::array<T, N>>> {
  constexpr static const char *prefix = "std::array [";
};

template <typename T, std::size_t N>
struct printer<T[N]> : detail::arraylike_base<T[N], printer<T[N]>> {
  constexpr static const char *prefix = "native array [";
};

template <typename... T>
struct printer<std::map<T...>>
    : detail::maplike_base<std::map<T...>, printer<std::map<T...>>> {
  constexpr static const char *prefix = "std::map [";
};

template <typename... T>
struct printer<std::multimap<T...>>
    : detail::maplike_base<std::multimap<T...>, printer<std::multimap<T...>>> {
  constexpr static const char *prefix = "std::multimap [";
};

template <typename... T>
struct printer<std::unordered_map<T...>>
    : detail::maplike_base<std::unordered_map<T...>,
                           printer<std::unordered_map<T...>>> {
  constexpr static const char *prefix = "std::unordered_map [";
};

template <typename... T>
struct printer<std::unordered_multimap<T...>>
    : detail::maplike_base<std::unordered_multimap<T...>,
                           printer<std::unordered_multimap<T...>>> {
  constexpr static const char *prefix = "std::unordered_multimap [";
};

} // namespace hippo

#endif // HIPPO_DETAIL_CONTAINERS_H_
