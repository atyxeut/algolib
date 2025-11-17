#ifndef AAL_SRC_IO_TUPLE_DETAIL_HPP
#define AAL_SRC_IO_TUPLE_DETAIL_HPP

#include <ostream>
#include <string_view>
#include <tuple>
#include <utility>

namespace aal { namespace detail {

template <typename TChar, typename... Ts, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<TChar>& ostr, const std::tuple<Ts...>& t, std::basic_string_view<TChar> delim, std::index_sequence<Is...>)
{
  ((ostr << std::get<Is>(t) << (Is + 1 == std::tuple_size_v<std::tuple<Ts...>> ? std::basic_string_view<TChar> {} : delim)), ...);
}

}} // namespace aal::detail

#endif // AAL_SRC_IO_TUPLE_DETAIL_HPP
