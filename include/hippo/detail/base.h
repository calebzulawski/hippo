#ifndef HIPPO_DETAIL_BASE_H_
#define HIPPO_DETAIL_BASE_H_

#include "type_name.h"
#include <cstdint>
#include <list>
#include <string>
#include <vector>

namespace hippo {

struct line {
  line() = delete;
  line(std::uint64_t indent) : indent(indent) {}
  line(std::uint64_t indent, std::string string)
      : indent(indent), string(string) {}

  std::string string;
  std::uint64_t indent;
};

template <typename T, typename U = T> struct printer;

template <typename T>
std::vector<std::string> print(const T &t, std::uint64_t indent = 2) {
  auto lines = ::hippo::printer<T>::print(t, 0);
  std::vector<std::string> output;
  output.reserve(lines.size());
  for (const auto &line : lines)
    output.emplace_back(
        std::string(indent * line.indent, ' ').append(line.string));
  return output;
}

} // namespace hippo

#endif // HIPPO_DETAIL_BASE_H_
