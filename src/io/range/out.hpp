#ifndef AAL_SRC_IO_RANGE_OUT_HPP
#define AAL_SRC_IO_RANGE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/io/range/out.hpp */

#include "../../type-traits/io.hpp"
#include "../../type-traits/range.hpp"
#include <cstddef>
#include <string>

namespace aal {

// element of the range can be printed by the specified ostr by default
// e.g. std::vector<std::string> can, but std::vector<std::pair<int, int>> can not
template <
  typename TChar, typename TTraits, typename TRange, typename TDelim,
  typename TVal = enable_if_t<is_range<TRange>::value, remove_cvref_t<decltype(*std::begin(std::declval<TRange>()))>>
>
auto print(std::basic_ostream<TChar, TTraits>& ostr, TRange&& range, TDelim&& delim, bool never_second_case = true) -> enable_if_t<
  std::is_convertible<remove_cvref_t<TDelim>, std::basic_string<TChar>>::value && is_default_printable<TVal, std::basic_ostream<TChar, TTraits>>::value, int
>
{
  auto cur_delim = never_second_case ? delim : std::basic_string<TChar>(1, static_cast<TChar>(' '));
  for (auto it = std::begin(range), it_end = std::end(range); it != it_end; ++it)
    ostr << *it << (std::next(it) == it_end ? std::basic_string<TChar> {} : cur_delim);
  return 1;
}

// element type of the range is non-default-printable range
// e.g. std::vector<std::array<int, 4>>
template <
  typename TChar, typename TTraits, typename TRange, typename TDelim,
  typename TVal = enable_if_t<is_range<TRange>::value, remove_cvref_t<decltype(*std::begin(std::declval<TRange>()))>>
>
auto print(std::basic_ostream<TChar, TTraits>& ostr, TRange&& range, TDelim&& delim, bool never_second_case = false)
  -> enable_if_t<std::is_convertible<remove_cvref_t<TDelim>, std::basic_string<TChar>>::value && is_range<TVal>::value, int>
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
template <typename TChar, typename TTraits, typename TRange>
auto operator <<(std::basic_ostream<TChar, TTraits>& ostr, TRange&& range) -> ::aal::enable_if_t<
  // the second condition is set to avoid ambiguous overloads when TRange is std::string, const char[N], ...
  ::aal::is_range<TRange>::value && !::aal::is_default_printable<TRange, std::basic_ostream<TChar, TTraits>>::value, std::basic_ostream<TChar, TTraits>&
>
{
  using TVal = ::aal::remove_cvref_t<decltype(*std::begin(std::declval<TRange>()))>;
  ::aal::print(
    ostr, std::forward<TRange>(range),
    std::basic_string<TChar>(1, static_cast<TChar>(::aal::is_default_printable<TVal, std::basic_ostream<TChar, TTraits>>::value ? ' ' : '\n'))
  );
  return ostr;
}

#endif // AAL_SRC_IO_RANGE_OUT_HPP
