#ifndef AAL_SRC_IO_DETAIL_TUPLE_OUT_HPP
#define AAL_SRC_IO_DETAIL_TUPLE_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/io/detail/tuple_out.hpp */

#include "../../integer_sequence.hpp"
#include <ostream>
#include <tuple>

namespace detail {

template <typename TChar, typename TTraits, typename TTuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<TChar, TTraits>& ostr, const TTuple& t, ::aal::index_sequence<Is...>)
{
  using T = int[];
  (void)(T {(ostr << std::get<Is>(t) << (Is + 1 == std::tuple_size<TTuple>::value ? "" : " "), 0)...});
}

} // namespace detail

#endif // AAL_SRC_IO_DETAIL_TUPLE_OUT_HPP
