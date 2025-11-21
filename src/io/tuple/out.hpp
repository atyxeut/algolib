#ifndef AAL_SRC_IO_TUPLE_OUT_HPP
#define AAL_SRC_IO_TUPLE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/io/tuple/out.hpp */

// to make the overload of operator << defined in range/out.hpp able to accept ranges that has std::pair, std::tuple as elements,
//   this #include order is necessary:
//   #include ".../tuple/out.hpp"
//   #include ".../range/out.hpp"

#include <concepts>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>

namespace aal {

template <typename TChar, typename T1, typename T2, typename TDelim> requires std::convertible_to<TDelim, std::basic_string<TChar>>
void print(std::basic_ostream<TChar>& ostr, const std::pair<T1, T2>& p, TDelim&& delim)
{
  ostr << p.first << delim << p.second;
}

template <typename TChar, typename... Ts, typename TDelim> requires std::convertible_to<TDelim, std::basic_string<TChar>>
void print(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t, TDelim&& delim)
{
  [&]<std::size_t... Is>(std::index_sequence<Is...>)
  {
    ((ostr << std::get<Is>(t) << (Is + 1 == std::tuple_size_v<std::tuple<Ts...>> ? std::basic_string<TChar> {} : delim)), ...);
  }(std::index_sequence_for<Ts...> {});
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
  ::aal::print(ostr, t, std::basic_string<TChar>(1, static_cast<TChar>(' ')));
  return ostr;
}

#endif // AAL_SRC_IO_TUPLE_OUT_HPP
