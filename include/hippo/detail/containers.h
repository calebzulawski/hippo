#ifndef HIPPO_DETAIL_CONTAINERS_H_
#define HIPPO_DETAIL_CONTAINERS_H_

#include "base.h"
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace hippo {

namespace detail {

template <typename Container> struct arraylike_base {

  static std::string suffix() { return "]"; }
  static std::vector<std::string> print(const Container &c,
                                        std::uint64_t indent,
                                        std::uint64_t current_indent) {
    std::vector<std::string> lines;
    for (const auto &element : c)
      ::hippo::detail::print_with_prefix(element, lines, indent,
                                         current_indent);
    return lines;
  }
};

template <typename Container> struct maplike_base {

  static std::string suffix() { return "]"; }
  static std::vector<std::string> print(const Container &c,
                                        std::uint64_t indent,
                                        std::uint64_t current_indent) {
    std::vector<std::string> lines;
    for (const auto &[key, value] : c) {
      std::string header(current_indent, ' ');
      header.push_back('(');
      lines.emplace_back(header);
      ::hippo::detail::print_with_prefix("key:", key, lines, indent,
                                         current_indent + indent);
      ::hippo::detail::print_with_prefix("value:", value, lines, indent,
                                         current_indent + indent);
      std::string footer(current_indent, ' ');
      footer.push_back(')');
      lines.emplace_back(footer);
    }
    return lines;
  }
};

} // namespace detail

template <typename... T>
struct printer<std::vector<T...>> : detail::arraylike_base<std::vector<T...>> {
  static std::string prefix() { return "std::vector ["; }
};

template <typename... T>
struct printer<std::list<T...>> : detail::arraylike_base<std::list<T...>> {
  static std::string prefix() { return "std::list ["; }
};

template <typename... T>
struct printer<std::forward_list<T...>>
    : detail::arraylike_base<std::forward_list<T...>> {
  static std::string prefix() { return "std::forward_list ["; }
};

template <typename... T>
struct printer<std::deque<T...>> : detail::arraylike_base<std::deque<T...>> {
  static std::string prefix() { return "std::deque ["; }
};

template <typename... T>
struct printer<std::set<T...>> : detail::arraylike_base<std::set<T...>> {
  static std::string prefix() { return "std::set ["; }
};

template <typename... T>
struct printer<std::multiset<T...>>
    : detail::arraylike_base<std::multiset<T...>> {
  static std::string prefix() { return "std::multiset ["; }
};

template <typename... T>
struct printer<std::unordered_set<T...>>
    : detail::arraylike_base<std::unordered_set<T...>> {
  static std::string prefix() { return "std::unordered_set ["; }
};

template <typename... T>
struct printer<std::unordered_multiset<T...>>
    : detail::arraylike_base<std::unordered_multiset<T...>> {
  static std::string prefix() { return "std::unordered_multiset ["; }
};

template <typename T, std::size_t N>
struct printer<std::array<T, N>> : detail::arraylike_base<std::array<T, N>> {
  static std::string prefix() { return "std::array ["; }
};

template <typename T, std::size_t N>
struct printer<T[N]> : detail::arraylike_base<T[N]> {
  static std::string prefix() { return "native array ["; }
};

template <typename... T>
struct printer<std::map<T...>> : detail::maplike_base<std::map<T...>> {
  static std::string prefix() { return "std::map ["; }
};

template <typename... T>
struct printer<std::multimap<T...>>
    : detail::maplike_base<std::multimap<T...>> {
  static std::string prefix() { return "std::multimap ["; }
};

template <typename... T>
struct printer<std::unordered_map<T...>>
    : detail::maplike_base<std::unordered_map<T...>> {
  static std::string prefix() { return "std::unordered_map ["; }
};

template <typename... T>
struct printer<std::unordered_multimap<T...>>
    : detail::maplike_base<std::unordered_multimap<T...>> {
  static std::string prefix() { return "std::unordered_multimap ["; }
};

} // namespace hippo

#endif // HIPPO_DETAIL_CONTAINERS_H_
