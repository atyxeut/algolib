#ifndef AAL_SRC_IO_TUPLE_OUT_HPP
#define AAL_SRC_IO_TUPLE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/io/tuple/out.hpp */

#include "detail.hpp"
#include <utility>

// to make the overload of operator << defined in range/out.hpp able to accept ranges that has std::pair, std::tuple as elements,
//   this #include order is necessary:
// #include ".../tuple/out.hpp"
// #include ".../range/out.hpp"

namespace aal {

template <typename TChar, typename TTraits, typename T1, typename T2, typename TDelim>
auto print(std::basic_ostream<TChar, TTraits>& ostr, const std::pair<T1, T2>& p, TDelim&& delim) ->
  typename std::enable_if<std::is_convertible<TDelim, std::basic_string<TChar>>::value, void>::type
{
  ostr << p.first << delim << p.second;
}

template <typename TChar, typename TTraits, typename TDelim, typename... Ts, std::size_t... Is>
auto print(std::basic_ostream<TChar, TTraits>& ostr, const std::tuple<Ts...>& t, TDelim&& delim) ->
  typename std::enable_if<std::is_convertible<TDelim, std::basic_string<TChar>>::value, void>::type
{
  detail::print_tuple_impl(ostr, t, std::forward<TDelim>(delim), index_sequence_for<Ts...> {});
}

} // namespace aal

template <typename TChar, typename TTraits, typename T1, typename T2>
auto operator <<(std::basic_ostream<TChar, TTraits>& ostr, const std::pair<T1, T2>& p) -> std::basic_ostream<TChar, TTraits>&
{
  ::aal::print(ostr, p, std::basic_string<TChar>(1, static_cast<TChar>(' ')));
  return ostr;
}

template <typename TChar, typename TTraits, typename... Ts>
auto operator <<(std::basic_ostream<TChar, TTraits>& ostr, const std::tuple<Ts...>& t) -> std::basic_ostream<TChar, TTraits>&
{
  ::aal::detail::print_tuple_impl(ostr, t, std::basic_string<TChar>(1, static_cast<TChar>(' ')), ::aal::index_sequence_for<Ts...> {});
  return ostr;
}

#endif // AAL_SRC_IO_TUPLE_OUT_HPP
