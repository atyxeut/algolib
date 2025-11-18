#ifndef AAL_SRC_IO_TUPLE_DETAIL_HPP
#define AAL_SRC_IO_TUPLE_DETAIL_HPP

#include <ostream>
#include <string>
#include <tuple>
#include <utility>

namespace aal { namespace detail {

template <typename TChar, typename... Ts, typename TDelim, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t, TDelim&& delim, std::index_sequence<Is...>)
{
  ((ostr << std::get<Is>(t) << (Is + 1 == std::tuple_size_v<std::tuple<Ts...>> ? std::basic_string<TChar> {} : delim)), ...);
}

}} // namespace aal::detail

#endif // AAL_SRC_IO_TUPLE_DETAIL_HPP
