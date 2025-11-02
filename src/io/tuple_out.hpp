#ifndef AAL_SRC_IO_TUPLE_OUT_HPP
#define AAL_SRC_IO_TUPLE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/io/tuple_out.hpp */

#include "detail/tuple_out.hpp"
#include <utility>

// this #include order is necesarry to make range_out.hpp able to print ranges that has std::pair, std::tuple as elements:
// #include <.../tuple_out.hpp>
// #include <.../range_out.hpp>

template <typename TChar, typename TTraits, typename T1, typename T2>
auto operator <<(std::basic_ostream<TChar, TTraits>& ostr, const std::pair<T1, T2>& p) -> std::basic_ostream<TChar, TTraits>&
{
  ostr << p.first << " " << p.second;
  return ostr;
}

template <typename TChar, typename TTraits, typename... Ts>
auto operator <<(std::basic_ostream<TChar, TTraits>& ostr, const std::tuple<Ts...>& t) -> std::basic_ostream<TChar, TTraits>&
{
  detail::print_tuple_impl(ostr, t, ::aal::index_sequence_for<Ts...> {});
  return ostr;
}

#endif // AAL_SRC_IO_TUPLE_OUT_HPP
