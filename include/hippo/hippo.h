#ifndef HIPPO_HIPPO_H_
#define HIPPO_HIPPO_H_

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace hippo {

template <typename T> struct printer {};

namespace detail {
template <typename T>
std::vector<std::string> deduce_print(const T &t, std::uint64_t width,
                                      std::uint64_t indent,
                                      std::uint64_t current_indent) {
  return ::hippo::printer<T>(t, width, indent, current_indent);
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
std::vector<std::string> print(const T &t, std::uint64_t width,
                               std::uint64_t indent) {
  return detail::deduce_print(t, width, indent, 0);
}

} // namespace hippo

#define DETAIL_HIPPO_LEADER(Name)                                              \
  std::string leader(' ', current_indent);                                     \
  leader.append(#Name ":");                                                    \
  lines.emplace_back(leader);

#define HIPPO_BEGIN(Type)                                                      \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    std::vector<std::string> print(const Type &t, std::uint64_t width,         \
                                   std::uint64_t indent,                       \
                                   std::uint64_t current_indent) {             \
      std::vector<std::string> lines;

#define HIPPO_END()                                                            \
  }                                                                            \
  }                                                                            \
  ;                                                                            \
  }

#define HIPPO_MEMBER(Name, Expression)                                         \
  {                                                                            \
    DETAIL_HIPPO_LEADER(Name);                                                 \
    auto sublines = ::hippo::detail::deduce_print((Expression), width, indent, \
                                                  current_indent + indent);    \
    lines.insert(lines.end(), std::begin(sublines), std::end(sublines));       \
  }

#define HIPPO_MEMBER_STREAM(Name, Expression)                                  \
  {                                                                            \
    DETAIL_HIPPO_LEADER(Name);                                                 \
    std::ostringstream ss;                                                     \
    ss << std::string(' ', current_indent) << (Expression);                    \
    auto sublines =                                                            \
        ::hippo::detail::split_and_indent(ss.str(), current_indent);           \
    lines.insert(lines.end(), std::begin(sublines), std::end(sublines));       \
  }

#endif // HIPPO_HIPPO_H_
