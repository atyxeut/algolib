#ifndef AAL_SRC_IO_RANGE_OUT_HPP
#define AAL_SRC_IO_RANGE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/io/range_out.hpp */

#include "../type-traits/io.hpp"
#include "../type-traits/range.hpp"

// print ranges whose element can be printed by default, e.g. std::vector<std::string> is OK but std::vector<std::pair<int, int>> is not
template <typename TRange, typename TChar, typename TTraits, typename TOstream = std::basic_ostream<TChar, TTraits>>
auto operator <<(std::basic_ostream<TChar, TTraits>& ostr, TRange&& range) -> ::aal::enable_if_t<
  ::aal::is_range<TRange>::value &&
    !::aal::is_default_printable<TRange, TOstream>::value &&
    ::aal::is_default_printable<::aal::remove_cvref_t<decltype(*std::begin(std::declval<TRange>()))>, TOstream>::value,
  TOstream&
>
{
  for (auto begin = std::begin(range), end = std::end(range); begin != end; ++begin)
    ostr << *begin << (std::next(begin) == end ? "" : " ");
  return ostr;
}

#endif // AAL_SRC_IO_RANGE_OUT_HPP
