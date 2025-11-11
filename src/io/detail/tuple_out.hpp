#ifndef AAL_SRC_IO_DETAIL_TUPLE_OUT_HPP
#define AAL_SRC_IO_DETAIL_TUPLE_OUT_HPP

#include "../../integer_sequence.hpp"
#include <ostream>
#include <string>
#include <tuple>

namespace aal { namespace detail {

template <typename TChar, typename TTraits, typename TDelim, typename... Ts, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<TChar, TTraits>& ostr, const std::tuple<Ts...>& t, TDelim&& delim, index_sequence<Is...>)
{
  using T = int[];
  static_cast<void>(T {(ostr << std::get<Is>(t) << (Is + 1 == std::tuple_size<std::tuple<Ts...>>::value ? std::basic_string<TChar> {} : delim), 0)...});
}

}} // namespace aal::detail

#endif // AAL_SRC_IO_DETAIL_TUPLE_OUT_HPP
