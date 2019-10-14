//! \file
#ifndef HIPPO_DETAIL_BASE_H_
#define HIPPO_DETAIL_BASE_H_

#include "type_name.h"
#include <cstdint>
#include <list>
#include <ostream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace hippo {

//! Describes a printed line of text
struct line {
  line() = delete;

  //! Construct an empty line with the given indentation level
  line(std::uint64_t indent) : indent(indent) {}

  //! Construct a line with the given indentation level and string
  line(std::uint64_t indent, std::string string)
      : indent(indent), string(string) {}

  std::uint64_t indent; //!< The indentation level of the line
  std::string string;   //!< The contents of the line
};

//! Describes the printed output of any object, either as a single or multiple
//! lines
using object = std::variant<::hippo::line, std::list<::hippo::line>>;

//! Visitor over `object`s that prepends a string to the first line
struct prepend_visitor {
  //! Prepend to a single line
  void operator()(::hippo::line &line) { line.string = prefix + line.string; }

  //! Prepend to the beginning of many lines
  void operator()(std::list<::hippo::line> &lines) {
    lines.front().string = prefix + lines.front().string;
  }
  std::string prefix; //!< The string to prepend
};

//! Visitor over `object`s that appends a string to the last line
struct append_visitor {
  //! Append to a single line
  void operator()(::hippo::line &line) { line.string += suffix; }

  //! Append to the end of many lines
  void operator()(std::list<::hippo::line> &lines) {
    lines.back().string += suffix;
  }
  std::string suffix; //!< The string to append
};

//! Global configuration values applied to all printers
struct configuration {
  std::uint64_t indent = 2; //!< The number of spaces to indent for each
                            //!< indentation level (defaults to 0)
  std::uint64_t width = 60; //!< The number of output columns, not a hard limit
                            //!< but best-effort (defaults to 60)
};

//! The core pretty-printer type. `T` is the type to be printed. `U` is provided
//! for optionally making SFINAE possible.
template <typename T, typename U = T> struct printer;

//! Specialization for printing const types
template <typename T> struct printer<const T> : hippo::printer<T> {};

//! Specialization for printing volatile types
template <typename T> struct printer<volatile T> : hippo::printer<T> {};

//! Specialization for printing const volatile types
template <typename T> struct printer<const volatile T> : hippo::printer<T> {};

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

//! Print any printable value `t` with configuration `config`
template <typename T>
std::vector<std::string> print(const T &t,
                               const ::hippo::configuration &config) {
  return std::visit(detail::print_visitor{config},
                    ::hippo::printer<T>::print(t, 0, config));
}

//! Print any printable value `t` with configuration `config` to the specified
//! `std::ostream`
template <typename T>
std::ostream &print_to(std::ostream &os, const T &t,
                       const ::hippo::configuration &config) {
  auto v = print(t, config);
  for (const auto &s : v)
    os << s << std::endl;
  return os;
}

//! Condense a collection of `line`s into a single `object`.
//! Multiple lines will be condensed into one if the indented result is less
//! than the configured output width.
inline ::hippo::object condense(const std::list<::hippo::line> &lines,
                                const ::hippo::configuration &config) {
  if (config.width == 0)
    return lines;

  std::uint64_t condensed_width = lines.front().indent * config.indent +
                                  lines.size() - 1; // indent and spaces
  for (const auto &line : lines)
    condensed_width += line.string.size();
  if (condensed_width <= config.width) {
    ::hippo::line condensed = lines.front();
    auto it = lines.begin();
    auto end = lines.end();
    if (it != end)
      ++it;
    for (; it != end; ++it)
      condensed.string += " " + it->string;
    return condensed;
  }
  return lines;
}

//! Condense a collection of `object`s into a single `object`.
//! If any of the input `object`s are multiline, the output is not condensed,
//! otherwise the lines will condensed if the indented result is less than the
//! configured output width.
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
  return condensable ? condense(lines, config) : lines;
}

} // namespace hippo

#endif // HIPPO_DETAIL_BASE_H_
