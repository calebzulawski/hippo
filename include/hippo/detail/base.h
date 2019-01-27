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

template <typename T>
void print_with_prefix(const char *name, const T &value,
                       std::vector<std::string> &lines, std::uint64_t indent,
                       std::uint64_t current_indent) {
  std::string header(current_indent, ' ');
  if (name)
    header.append(name);
  if constexpr (::hippo::has_stringifier<T>::value) {
    if (name)
      header.push_back(' ');
    header.append(::hippo::stringifier<T>::stringify(value));
    lines.emplace_back(std::move(header));
  } else {
    if constexpr (::hippo::has_prefix_v<T>) {
      if (name)
        header.push_back(' ');
      auto prefix = ::hippo::printer<T>::prefix();
      if (prefix.size() > 0)
        header.append(prefix);
    }
    lines.emplace_back(std::move(header));
    auto sublines =
        ::hippo::printer<T>::print(value, indent, current_indent + indent);
    lines.insert(lines.end(), std::begin(sublines), std::end(sublines));
    if constexpr (::hippo::has_suffix_v<T>) {
      auto suffix = ::hippo::printer<T>::suffix();
      if (suffix.size() > 0) {
        std::string footer(current_indent, ' ');
        footer.append(suffix);
        lines.emplace_back(std::move(footer));
      }
    }
  }
}

template <typename T>
void print_with_prefix(const T &value, std::vector<std::string> &lines,
                       std::uint64_t indent, std::uint64_t current_indent) {
  print_with_prefix(nullptr, value, lines, indent, current_indent);
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

  auto contains = ::hippo::printer<T>::print(t, indent, current_indent);
  lines.insert(lines.end(), contains.begin(), contains.end());

  if constexpr (::hippo::has_suffix_v<T>) {
    lines.emplace_back(::hippo::printer<T>::suffix());
  }

  return lines;
}

} // namespace hippo

#endif // HIPPO_DETAIL_BASE_H_
