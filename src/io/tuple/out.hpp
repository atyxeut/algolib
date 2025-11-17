#ifndef AAL_SRC_IO_TUPLE_OUT_HPP
#define AAL_SRC_IO_TUPLE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/io/tuple/out.hpp */

#include "detail.hpp"
#include <string>

// to make the overload of operator << defined in range/out.hpp able to accept ranges that has std::pair, std::tuple as elements,
//   this #include order is necessary:
//   #include ".../tuple/out.hpp"
//   #include ".../range/out.hpp"

namespace aal {

template <typename TChar, typename T1, typename T2>
void print(std::basic_ostream<TChar>& ostr, const std::pair<T1, T2>& p, std::basic_string_view<TChar> delim)
{
  ostr << p.first << delim << p.second;
}

template <typename TChar, typename... Ts, std::size_t... Is>
void print(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t, std::basic_string_view<TChar> delim)
{
  detail::print_tuple_impl(ostr, t, delim, std::index_sequence_for<Ts...> {});
}

} // namespace aal

template <typename TChar, typename T1, typename T2>
decltype(auto) operator <<(std::basic_ostream<TChar>& ostr, const std::pair<T1, T2>& p)
{
  ::aal::print(ostr, p, std::basic_string_view<TChar> {std::basic_string<TChar>(1, static_cast<TChar>(' '))});
  return ostr;
}

template <typename TChar, typename... Ts>
decltype(auto) operator <<(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t)
{
  ::aal::detail::print_tuple_impl(
    ostr, t, std::basic_string_view<TChar> {std::basic_string<TChar>(1, static_cast<TChar>(' '))}, std::index_sequence_for<Ts...> {}
  );
  return ostr;
}

#endif // AAL_SRC_IO_TUPLE_OUT_HPP
