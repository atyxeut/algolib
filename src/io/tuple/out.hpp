#ifndef AAL_SRC_IO_TUPLE_OUT_HPP
#define AAL_SRC_IO_TUPLE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/io/tuple/out.hpp */

#include <concepts>

#include "detail.hpp"

// to make the overload of operator << defined in range/out.hpp able to accept ranges that has std::pair, std::tuple as elements,
//   this #include order is necessary:
//   #include ".../tuple/out.hpp"
//   #include ".../range/out.hpp"

namespace aal {

template <typename TChar, typename T1, typename T2, typename TDelim> requires std::convertible_to<TDelim, std::basic_string<TChar>>
void print(std::basic_ostream<TChar>& ostr, const std::pair<T1, T2>& p, TDelim&& delim)
{
  ostr << p.first << delim << p.second;
}

template <typename TChar, typename... Ts, typename TDelim, std::size_t... Is> requires std::convertible_to<TDelim, std::basic_string<TChar>>
void print(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t, TDelim&& delim)
{
  detail::print_tuple_impl(ostr, t, std::forward<TDelim>(delim), std::index_sequence_for<Ts...> {});
}

} // namespace aal

template <typename TChar, typename T1, typename T2>
decltype(auto) operator <<(std::basic_ostream<TChar>& ostr, const std::pair<T1, T2>& p)
{
  ::aal::print(ostr, p, std::basic_string<TChar>(1, static_cast<TChar>(' ')));
  return ostr;
}

template <typename TChar, typename... Ts>
decltype(auto) operator <<(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t)
{
  ::aal::detail::print_tuple_impl(ostr, t, std::basic_string<TChar>(1, static_cast<TChar>(' ')), std::index_sequence_for<Ts...> {});
  return ostr;
}

#endif // AAL_SRC_IO_TUPLE_OUT_HPP
