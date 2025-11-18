#ifndef AAL_SRC_IO_TUPLE_DETAIL_HPP
#define AAL_SRC_IO_TUPLE_DETAIL_HPP

#include "../../misc/integer_sequence.hpp"
#include <ostream>
#include <string>
#include <tuple>

namespace aal { namespace detail {

template <typename TChar, typename... Ts, typename TDelim, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t, TDelim&& delim, index_sequence<Is...>)
{
  using T = int[];
  static_cast<void>(T {(ostr << std::get<Is>(t) << (Is + 1 == std::tuple_size<std::tuple<Ts...>>::value ? std::basic_string<TChar> {} : delim), 0)...});
}

}} // namespace aal::detail

#endif // AAL_SRC_IO_TUPLE_DETAIL_HPP
