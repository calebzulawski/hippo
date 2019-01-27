#ifndef HIPPO_HIPPO_H_
#define HIPPO_HIPPO_H_

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace hippo {

template <typename T, typename U = T> struct printer;
template <typename T, typename U = T> struct stringifier;

template <typename T>
struct stringifier<
    T, typename std::enable_if<std::is_arithmetic<T>::value, T>::type> {
  static std::string stringify(const T &t) { return std::to_string(t); }
};

namespace detail {

template <typename, typename = std::void_t<>>
struct has_stringifier : std::false_type {};

template <typename T>
struct has_stringifier<T,
                       std::void_t<decltype(::hippo::stringifier<T>::stringify(
                           std::declval<T>()))>> : std::true_type {};

template <typename T>
inline constexpr bool has_stringifier_v = has_stringifier<T>::value;

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

template <typename T>
void print_member(const char *name, const T &value,
                  std::vector<std::string> &lines, std::uint64_t indent,
                  std::uint64_t current_indent) {
  std::string header(current_indent, ' ');
  header.append(name);
  if constexpr (::hippo::detail::has_stringifier<T>::value) {
    header.push_back(' ');
    header.append(::hippo::stringifier<T>::stringify(value));
    lines.emplace_back(std::move(header));
  } else {
    auto prefix = ::hippo::printer<T>::prefix();
    if (prefix.size() > 0)
      header.append(prefix);
    lines.emplace_back(std::move(header));
    auto sublines =
        ::hippo::detail::deduce_print(value, indent, current_indent + indent);
    lines.insert(lines.end(), std::begin(sublines), std::end(sublines));
    auto suffix = ::hippo::printer<T>::suffix();
    if (suffix.size() > 0) {
      std::string footer(current_indent, ' ');
      footer.append(suffix);
      lines.emplace_back(std::move(footer));
    }
  }
}

} // namespace detail

template <typename T>
std::vector<std::string> print(const T &t, std::uint64_t indent) {
  return detail::deduce_print(t, indent, 0);
}

} // namespace hippo

#define HIPPO_BEGIN(Type)                                                      \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    static std::string prefix() { return " {"; }                               \
    static std::string suffix() { return "}"; }                                \
    static std::vector<std::string> print(const Type &t, std::uint64_t indent, \
                                          std::uint64_t current_indent) {      \
      std::vector<std::string> lines;

#define HIPPO_END()                                                            \
  return lines;                                                                \
  }                                                                            \
  }                                                                            \
  ;                                                                            \
  }

#define HIPPO_MEMBER_EXPR(Name, Expression)                                    \
  {                                                                            \
    using Type = decltype(Expression);                                         \
    ::hippo::detail::print_member(#Name ":", (Expression), lines, indent,      \
                                  current_indent);                             \
  }

#define HIPPO_MEMBER(Name) HIPPO_MEMBER_EXPR(Name, t.Name)

#endif // HIPPO_HIPPO_H_
