#ifndef AAL_SRC_IO_RANGE_OUT_HPP
#define AAL_SRC_IO_RANGE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/io/range/out.hpp */

#include "../../type-trait/io.hpp"
#include "../../type-trait/range.hpp"
#include <cstddef>
#include <string>

namespace aal {

// element of the range can be printed by the specified ostr by default
// e.g. std::vector<std::string> can, but std::vector<std::pair<int, int>> can not
template <
  typename TChar, typename TRange, typename TDelim,
  typename TVal = enable_if_t<is_range<TRange>::value, remove_cvref_t<decltype(*std::begin(std::declval<TRange&>()))>>
>
auto print(std::basic_ostream<TChar>& ostr, TRange&& range, TDelim&& delim, bool never_second_case = true)
  -> enable_if_t<is_ostream_interactable<TChar, TVal>::value && std::is_convertible<TDelim, std::basic_string<TChar>>::value, int>
{
  auto cur_delim = never_second_case ? delim : std::basic_string<TChar>(1, static_cast<TChar>(' '));
  for (auto it = std::begin(range), it_end = std::end(range); it != it_end; ++it)
    ostr << *it << (std::next(it) == it_end ? std::basic_string<TChar> {} : cur_delim);
  return 1;
}

// element type of the range is non-default-printable range
// e.g. std::vector<std::array<int, 4>>
template <
  typename TChar, typename TRange, typename TDelim,
  typename TVal = enable_if_t<is_range<TRange>::value, remove_cvref_t<decltype(*std::begin(std::declval<TRange&>()))>>
>
auto print(std::basic_ostream<TChar>& ostr, TRange&& range, TDelim&& delim, bool never_second_case = false)
  -> enable_if_t<is_range<TVal>::value && std::is_convertible<TDelim, std::basic_string<TChar>>::value, int>
{
  int reverse_dep = 0;
  for (auto it = std::begin(range), it_end = std::end(range); it != it_end; ++it) {
    reverse_dep = print(ostr, *it, std::forward<TDelim>(delim), never_second_case);
    auto cur_delim = std::basic_string<TChar>(static_cast<std::size_t>(reverse_dep), *std::begin(delim));
    ostr << (std::next(it) == it_end ? std::basic_string<TChar> {} : cur_delim);
  }
  return reverse_dep + 1;
}

} // namespace aal

// call aal::print with a space or a new line character as the delimiter (depending on whether it is a nested range)
template <typename TChar, typename TRange, typename TVal = ::aal::remove_cvref_t<decltype(*std::begin(std::declval<TRange&>()))>>
auto operator <<(std::basic_ostream<TChar>& ostr, TRange&& range) -> ::aal::enable_if_t<
  // the second condition is set to avoid ambiguous overloads when TRange is std::string, const char[N], ...
  ::aal::is_range<TRange>::value && !::aal::is_ostream_interactable<TChar, TRange>::value, std::basic_ostream<TChar>&
>
{
  ::aal::print(
    ostr, std::forward<TRange>(range), std::basic_string<TChar>(1, static_cast<TChar>(::aal::is_ostream_interactable<TChar, TVal>::value ? ' ' : '\n'))
  );
  return ostr;
}

#endif // AAL_SRC_IO_RANGE_OUT_HPP
