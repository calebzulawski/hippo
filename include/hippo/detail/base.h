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

// line
struct line {
  line() = delete;
  line(std::uint64_t indent) : indent(indent) {}
  line(std::uint64_t indent, std::string string)
      : indent(indent), string(string) {}

  std::string string;
  std::uint64_t indent;
};

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
template <typename T, typename U = T> struct printer;

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
std::vector<::hippo::line> print_with_prefix(const char *name, const T &value,
                                             std::uint64_t current_indent) {
  std::vector<::hippo::line> lines;
  if constexpr (::hippo::has_stringifier<T>::value) {
    ::hippo::line line(current_indent);
    if (name) {
      line.string.append(name);
      line.string.push_back(' ');
    }
    line.string.append(::hippo::stringifier<T>::stringify(value));
    lines.emplace_back(std::move(line));
  } else {
    if constexpr (::hippo::has_prefix_v<T>) {
      ::hippo::line header(current_indent);
      if (name) {
        header.string.append(name);
        header.string.push_back(' ');
      }
      header.string.append(::hippo::printer<T>::prefix());
      lines.emplace_back(std::move(header));
    }
    auto sublines = ::hippo::printer<T>::print(value, current_indent + 1);
    lines.insert(lines.end(), std::begin(sublines), std::end(sublines));
    if constexpr (::hippo::has_suffix_v<T>) {
      lines.emplace_back(current_indent, ::hippo::printer<T>::suffix());
    }
  }
  return lines;
}

template <typename T>
std::vector<::hippo::line> print_with_prefix(const T &value,
                                             std::uint64_t current_indent) {
  return print_with_prefix(nullptr, value, current_indent);
}

} // namespace detail

template <typename T>
std::vector<std::string> print(const T &t, std::uint64_t indent = 2) {
  auto lines = ::hippo::detail::print_with_prefix(t, 0);
  std::vector<std::string> output;
  for (const auto &line : lines)
    output.emplace_back(
        std::string(indent * line.indent, ' ').append(line.string));
  return output;
}

} // namespace hippo

#endif // HIPPO_DETAIL_BASE_H_
