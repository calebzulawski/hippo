#ifndef HIPPO_DETAIL_BASE_H_
#define HIPPO_DETAIL_BASE_H_

#include "type_name.h"
#include <cstdint>
#include <list>
#include <string>
#include <utility>
#include <variant>
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

using object = std::variant<::hippo::line, std::list<::hippo::line>>;

struct prepend_visitor {
  void operator()(::hippo::line &line) { line.string = prefix + line.string; }
  void operator()(std::list<::hippo::line> &lines) {
    lines.front().string = prefix + lines.front().string;
  }
  std::string prefix;
};

struct append_visitor {
  void operator()(::hippo::line &line) { line.string += suffix; }
  void operator()(std::list<::hippo::line> &lines) {
    lines.back().string += suffix;
  }
  std::string suffix;
};

template <typename T, typename U = T> struct printer;

struct configuration {
  std::uint64_t indent = 2;
  std::uint64_t width = 60;
};

namespace detail {
struct print_visitor {
  std::vector<std::string> operator()(const ::hippo::line &line) {
    std::vector<std::string> output;
    output.emplace_back(config.indent * line.indent, ' ');
    output.back() += line.string;
    return output;
  }
  std::vector<std::string> operator()(const std::list<::hippo::line> &lines) {
    std::vector<std::string> output;
    output.reserve(lines.size());
    for (const auto &line : lines)
      output.emplace_back(
          std::string(config.indent * line.indent, ' ').append(line.string));
    return output;
  }
  const ::hippo::configuration &config;
};

struct condense_visitor {
  std::pair<std::list<::hippo::line>, bool>
  operator()(const ::hippo::line &line) {
    return {{{line}}, true};
  }
  std::pair<std::list<::hippo::line>, bool>
  operator()(const std::list<::hippo::line> &lines) {
    return {lines, false};
  }
};
} // namespace detail

template <typename T>
std::vector<std::string> print(const T &t,
                               const ::hippo::configuration &config) {
  return std::visit(detail::print_visitor{config},
                    ::hippo::printer<T>::print(t, 0, config));
}

inline ::hippo::object condense(const std::list<::hippo::object> &objects,
                                const ::hippo::configuration &config) {
  std::list<::hippo::line> lines;
  bool condensable = true;
  for (const auto &o : objects) {
    auto [this_lines, this_condense] =
        std::visit(detail::condense_visitor{}, o);
    lines.splice(lines.end(), this_lines);
    condensable &= this_condense;
  }
  if (config.width == 0)
    condensable = false;

  if (condensable) {
    std::uint64_t condensed_width = lines.front().indent * config.indent +
                                    lines.size() - 1; // indent and spaces
    for (const auto &line : lines)
      condensed_width += line.string.size();
    if (condensed_width <= config.width) {
      ::hippo::line condensed = lines.front();
      lines.pop_front();
      for (const auto &line : lines) {
        condensed.string += " " + line.string;
      }
      return condensed;
    }
  }

  return lines;
}

} // namespace hippo

#endif // HIPPO_DETAIL_BASE_H_
