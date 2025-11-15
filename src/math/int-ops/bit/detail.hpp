#ifndef AAL_SRC_MATH_INT_OPS_BIT_DETAIL_HPP
#define AAL_SRC_MATH_INT_OPS_BIT_DETAIL_HPP

#include "../../../type-traits/integral.hpp"
#include <limits>

namespace aal { namespace detail { namespace bit {

template <std::size_t Width, typename T>
constexpr auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u32>::digits, int>::type
{
  return std::numeric_limits<make_unsigned_t<T>>::digits + __builtin_clz(x) - static_cast<int>(Width);
}

template <std::size_t Width, typename T>
auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u64>::digits, int>::type
{
  return __builtin_clzll(x);
}

template <std::size_t Width, typename T>
auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u128>::digits, int>::type
{
  return __builtin_clzg(static_cast<u128>(x));
}

}}} // namespace aal::detail::bit

#endif // AAL_SRC_MATH_INT_OPS_BIT_DETAIL_HPP
