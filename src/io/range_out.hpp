#ifndef AAL_SRC_IO_RANGE_OUT_HPP
#define AAL_SRC_IO_RANGE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/io/range_out.hpp */

#include "../type-traits/io.hpp"
#include "../type-traits/range.hpp"
#include <string>

namespace aal {

// print ranges whose element can be printed by specific ostreams by default
// e.g. std::vector<std::string> is OK but std::vector<std::pair<int, int>> is not by default
template <typename TChar, typename TTraits, typename TRange, typename TDelim>
auto print_range(std::basic_ostream<TChar, TTraits>& ostr, TRange&& range, TDelim&& delim) -> enable_if_t<
  is_range<TRange>::value &&
    is_default_printable<remove_cvref_t<decltype(*std::begin(std::declval<TRange>()))>, std::basic_ostream<TChar, TTraits>>::value &&
    std::is_convertible<remove_cvref_t<TDelim>, std::basic_string<TChar>>::value,
  void
>
{
  for (auto begin = std::begin(range), end = std::end(range); begin != end; ++begin)
    ostr << *begin << (std::next(begin) == end ? std::basic_string<TChar> {} : delim);
}

} // namespace aal

// call aal::print_range with a space as the delimiter
template <typename TChar, typename TTraits, typename TRange>
auto operator <<(std::basic_ostream<TChar, TTraits>& ostr, TRange&& range) -> ::aal::enable_if_t<
  // the second condition is set to avoid ambiguous overloads when TRange is std::string, const char*, ...
  ::aal::is_range<TRange>::value && !::aal::is_default_printable<TRange, std::basic_ostream<TChar, TTraits>>::value, std::basic_ostream<TChar, TTraits>&
>
{
  ::aal::print_range(ostr, std::forward<TRange>(range), std::basic_string<TChar>(1, static_cast<TChar>(' ')));
  return ostr;
}

#endif // AAL_SRC_IO_RANGE_OUT_HPP
