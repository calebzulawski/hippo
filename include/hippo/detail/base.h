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

struct configuration {
  std::uint64_t indent = 2;
  std::uint64_t width = 60;
};

template <typename T>
std::vector<std::string> print(const T &t,
                               const ::hippo::configuration &config) {
  auto lines = ::hippo::printer<T>::print(t, 0, config);
  condense(lines, config);
  std::vector<std::string> output;
  output.reserve(lines.size());
  for (const auto &line : lines)
    output.emplace_back(
        std::string(config.indent * line.indent, ' ').append(line.string));
  return output;
}

void condense(std::list<::hippo::line> &lines,
              const ::hippo::configuration &config) {
  if (config.width == 0)
    return;
  std::uint64_t condensed_width = lines.front().indent * config.indent +
                                  lines.size() - 1; // indent and spaces
  for (const auto &line : lines)
    condensed_width += line.string.size();
  if (condensed_width > config.width)
    return;
  ::hippo::line condensed = lines.front();
  lines.pop_front();
  for (const auto &line : lines) {
    condensed.string += " " + line.string;
  }
  lines.clear();
  lines.emplace_back(condensed);
}

} // namespace hippo

#endif // HIPPO_DETAIL_BASE_H_
