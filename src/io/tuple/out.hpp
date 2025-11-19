#ifndef AAL_SRC_IO_TUPLE_OUT_HPP
#define AAL_SRC_IO_TUPLE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/io/tuple/out.hpp */

// to make the overload of operator << defined in range/out.hpp able to accept ranges that has std::pair, std::tuple as elements,
//   this #include order is necessary:
//   #include ".../tuple/out.hpp"
//   #include ".../range/out.hpp"

#include <ostream>
#include <string>
#include <tuple>
#include <utility>

#include "../../misc/integer_sequence.hpp"

namespace aal {

namespace io { namespace tuple { namespace detail {

template <typename TChar, typename... Ts, typename TDelim, std::size_t... Is>
void print_impl(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t, TDelim&& delim, index_sequence<Is...>)
{
  using T = int[];
  static_cast<void>(T {(ostr << std::get<Is>(t) << (Is + 1 == std::tuple_size<std::tuple<Ts...>>::value ? std::basic_string<TChar> {} : delim), 0)...});
}

}}} // namespace io::tuple::detail

template <typename TChar, typename T1, typename T2, typename TDelim>
auto print(std::basic_ostream<TChar>& ostr, const std::pair<T1, T2>& p, TDelim&& delim) ->
  typename std::enable_if<std::is_convertible<TDelim, std::basic_string<TChar>>::value>::type
{
  ostr << p.first << delim << p.second;
}

template <typename TChar, typename... Ts, typename TDelim, std::size_t... Is>
auto print(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t, TDelim&& delim) ->
  typename std::enable_if<std::is_convertible<TDelim, std::basic_string<TChar>>::value>::type
{
  io::tuple::detail::print_impl(ostr, t, std::forward<TDelim>(delim), index_sequence_for<Ts...> {});
}

} // namespace aal

template <typename TChar, typename T1, typename T2>
auto operator <<(std::basic_ostream<TChar>& ostr, const std::pair<T1, T2>& p) -> std::basic_ostream<TChar>&
{
  ::aal::print(ostr, p, std::basic_string<TChar>(1, static_cast<TChar>(' ')));
  return ostr;
}

template <typename TChar, typename... Ts>
auto operator <<(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t) -> std::basic_ostream<TChar>&
{
  ::aal::print(ostr, t, std::basic_string<TChar>(1, static_cast<TChar>(' ')));
  return ostr;
}

#endif // AAL_SRC_IO_TUPLE_OUT_HPP
