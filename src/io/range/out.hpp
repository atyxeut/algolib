<<<<<<< Updated upstream
#ifndef AAL_SRC_IO_RANGE_OUT_HPP
#define AAL_SRC_IO_RANGE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/io/range/out.hpp */

#include "../../type-trait/io.hpp"
#include <concepts>
#include <cstddef>
#include <ranges>
#include <string>

namespace aal {

template <typename TChar, std::ranges::input_range TRange, typename TDelim> requires std::convertible_to<TDelim, std::basic_string<TChar>>
int print(std::basic_ostream<TChar>& ostr, TRange&& range, TDelim&& delim, bool never_second_case = true)
{
  using value_type = std::ranges::range_value_t<TRange>;

  // element of the range can be printed by the specified ostr by default
  // e.g. std::vector<std::string> can, but std::vector<std::pair<int, int>> can not
  if constexpr (is_ostream_interactable_v<TChar, value_type>) {
    auto cur_delim = never_second_case ? delim : std::basic_string<TChar>(1, static_cast<TChar>(' '));
    for (auto it = std::begin(range), it_end = std::end(range); it != it_end; ++it)
      ostr << *it << (std::next(it) == it_end ? std::basic_string<TChar> {} : cur_delim);
    return 1;
  }

  // element type of the range is non-default-printable range
  // e.g. std::vector<std::array<int, 4>>
  if constexpr (std::ranges::input_range<value_type>) {
    int reverse_dep = 0;
    for (auto it = std::begin(range), it_end = std::end(range); it != it_end; ++it) {
      reverse_dep = print(ostr, *it, std::forward<TDelim>(delim), false);
      auto cur_delim = std::basic_string<TChar>(static_cast<std::size_t>(reverse_dep), *std::begin(delim));
      ostr << (std::next(it) == it_end ? std::basic_string<TChar> {} : cur_delim);
    }
    return reverse_dep + 1;
  }
}

} // namespace aal

// call aal::print with a space or a new line character as the delimiter (depending on whether it is a nested range)
// SFINAE here to avoid ambiguous overloads when TRange is std::string&, const char(&)[N], ...
// note that we cannot use requires here, since it sees the defining function template, causing infinitely recursivive constraint
template <typename TChar, std::ranges::input_range TRange, typename = std::enable_if_t<!::aal::is_ostream_interactable_v<TChar, TRange>>>
decltype(auto) operator <<(std::basic_ostream<TChar>& ostr, TRange&& range)
{
  ::aal::print(
    ostr, std::forward<TRange>(range),
    std::basic_string<TChar>(1, static_cast<TChar>(::aal::is_ostream_interactable_v<TChar, std::ranges::range_value_t<TRange>> ? ' ' : '\n'))
  );
  return ostr;
}

#endif // AAL_SRC_IO_RANGE_OUT_HPP
=======
#ifndef AAL_SRC_IO_RANGE_OUT_HPP
#define AAL_SRC_IO_RANGE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/io/range/out.hpp */

#include "../../concept/io.hpp"
#include <cstddef>
#include <iterator>
#include <ranges>
#include <string>
#include <utility>

namespace aal {

template <typename TChar, std::ranges::input_range TRange>
int print(std::basic_ostream<TChar>& ostr, TRange&& range, std::basic_string_view<TChar> delim, bool never_second_case = true)
{
  using value_type = std::iter_value_t<decltype(std::begin(range))>;

  // element of the range can be printed by the specified ostr by default
  // e.g. std::vector<std::string> can, but std::vector<std::pair<int, int>> can not
  if constexpr (ostream_default_interactable<TChar, value_type>) {
    auto cur_delim = never_second_case ? delim : std::basic_string_view<TChar> {std::basic_string<TChar>(1, static_cast<TChar>(' '))};
    for (auto it = std::begin(range), it_end = std::end(range); it != it_end; ++it)
      ostr << *it << (std::next(it) == it_end ? std::basic_string_view<TChar> {} : cur_delim);
    return 1;
  }

  // element type of the range is non-default-printable range
  // e.g. std::vector<std::array<int, 4>>
  if constexpr (std::ranges::input_range<value_type>) {
    int reverse_dep = 0;
    for (auto it = std::begin(range), it_end = std::end(range); it != it_end; ++it) {
      reverse_dep = print(ostr, *it, delim, never_second_case);
      auto cur_delim = std::basic_string<TChar>(static_cast<std::size_t>(reverse_dep), *std::begin(delim));
      ostr << (std::next(it) == it_end ? std::basic_string_view<TChar> {} : cur_delim);
    }
    return reverse_dep + 1;
  }
}

} // namespace aal

// call aal::print with a space or a new line character as the delimiter (depending on whether it is a nested range)
template <typename TChar, std::ranges::input_range TRange>
// avoid ambiguous overloads when TRange is std::string, const char[N], ...
requires (!::aal::ostream_default_interactable<TChar, TRange>)
decltype(auto) operator <<(std::basic_ostream<TChar>& ostr, TRange&& range)
{
  using value_type = std::iter_value_t<decltype(std::begin(range))>;

  ::aal::print(
    ostr, std::forward<TRange>(range),
    std::basic_string_view<TChar> {std::basic_string<TChar>(1, static_cast<TChar>(::aal::ostream_default_interactable<TChar, value_type> ? ' ' : '\n'))}
  );
  return ostr;
}

#endif // AAL_SRC_IO_RANGE_OUT_HPP
>>>>>>> Stashed changes
