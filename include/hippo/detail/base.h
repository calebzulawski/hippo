#ifndef HIPPO_DETAIL_BASE_H_
#define HIPPO_DETAIL_BASE_H_

#include "type_name.h"
#include <cstdint>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

namespace hippo {

// stringifier
template <typename T, typename U = T> struct stringifier;

// has_stringifier
template <typename, typename = void>
struct has_stringifier : std::false_type {};

template <typename T>
struct has_stringifier<T,
                       std::void_t<decltype(::hippo::stringifier<T>::stringify(
                           std::declval<T>()))>> : std::true_type {};

template <typename T>
inline constexpr bool has_stringifier_v = has_stringifier<T>::value;

// printer
template <typename T, typename U = std::enable_if_t<!has_stringifier_v<T>, T>>
struct printer;

// has_prefix
template <typename, typename = void> struct has_prefix : std::false_type {};

template <typename T>
struct has_prefix<T, std::enable_if_t<std::is_same_v<
                         decltype(::hippo::printer<T>::prefix()), std::string>>>
    : std::true_type {};

template <typename T> inline constexpr bool has_prefix_v = has_prefix<T>::value;

// has_suffix
template <typename, typename = void> struct has_suffix : std::false_type {};

template <typename T>
struct has_suffix<T, std::enable_if_t<std::is_same_v<
                         decltype(::hippo::printer<T>::suffix()), std::string>>>
    : std::true_type {};

template <typename T> inline constexpr bool has_suffix_v = has_suffix<T>::value;

namespace detail {

template <typename T>
std::vector<std::string> deduce_print(const T &t, std::uint64_t indent,
                                      std::uint64_t current_indent) {
  return ::hippo::printer<T>::print(t, indent, current_indent);
}

std::vector<std::string> split_and_indent(const std::string &s,
                                          std::uint64_t current_indent) {
  std::istringstream ss(s);
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(ss, line)) {
    lines.emplace_back(line.insert(0, current_indent, ' '));
  }
  return lines;
}

} // namespace detail

template <typename T>
std::vector<std::string> print(const T &t, std::uint64_t indent) {
  std::uint64_t current_indent = 0;
  std::vector<std::string> lines;
  if constexpr (::hippo::has_prefix_v<T>) {
    current_indent += indent;
    lines.emplace_back(::hippo::printer<T>::prefix());
  }

  auto contains = detail::deduce_print(t, indent, current_indent);
  lines.insert(lines.end(), contains.begin(), contains.end());

  if constexpr (::hippo::has_suffix_v<T>) {
    lines.emplace_back(::hippo::printer<T>::suffix());
  }

  return lines;
}

} // namespace hippo

#endif // HIPPO_DETAIL_BASE_H_
