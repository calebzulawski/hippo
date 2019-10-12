#ifndef HIPPO_STD_CHRONO_H_
#define HIPPO_STD_CHRONO_H_

#include "../hippo.h"
#include <chrono>
#include <list>
#include <sstream>
#include <type_traits>

namespace hippo {

//! Format for durations
template <typename T, typename Enable = void> struct duration_format;

//! Format for integer durations
template <typename T>
struct duration_format<T, std::enable_if_t<std::is_integral_v<T>>> {
  integer_format number_format; //!< Integer format configuration
};

//! Format for floating-point durations
template <typename T>
struct duration_format<T, std::enable_if_t<std::is_floating_point_v<T>>> {
  float_format number_format; //!< Floating-point format configuration
};

//!\cond
template <typename Rep, typename Period>
struct printer<std::chrono::duration<Rep, Period>> {
  using format_type = typename ::hippo::duration_format<Rep>;
  static ::hippo::object print(const std::chrono::duration<Rep, Period> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    std::list<::hippo::object> objects;

    std::string unit;
    if constexpr (std::is_same_v<Period, std::nano>)
      unit = " nanoseconds";
    else if (std::is_same_v<Period, std::micro>)
      unit = " microseconds";
    else if (std::is_same_v<Period, std::milli>)
      unit = " milliseconds";
    else if (std::is_same_v<Period, std::ratio<1>>)
      unit = " seconds";
    else if (std::is_same_v<Period, std::ratio<60>>)
      unit = " minutes";
    else if (std::is_same_v<Period, std::ratio<3600>>)
      unit = " hours";
    else if (std::is_same_v<Period, std::ratio<86400>>)
      unit = " days";
    else if (std::is_same_v<Period, std::ratio<604800>>)
      unit = " weeks";
    else if (std::is_same_v<Period, std::ratio<2629746>>)
      unit = " months";
    else if (std::is_same_v<Period, std::ratio<31556952>>)
      unit = " years";
    else if (Period::den == 1)
      unit = " " + std::to_string(Period::num) + "-seconds";
    else
      unit = " (" + std::to_string(Period::num) + "/" +
             std::to_string(Period::den) + ")-seconds";

    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "std::chrono::duration containing [");
    std::ostringstream ss;
    ss << ::hippo::apply_format(o.count(), format.number_format) << unit;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent + 1,
                         ss.str());
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "]");
    return ::hippo::condense(objects, config);
  }
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_CHRONO_H_
