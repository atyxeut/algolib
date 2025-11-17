#ifndef AAL_SRC_MATH_INT_OPERATION_GCD_INCLUDE_HPP
#define AAL_SRC_MATH_INT_OPERATION_GCD_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-operation/gcd/include.hpp */

#include "../../operator/gcd/include.hpp"
#include "detail.hpp"

// see note.md for extra information

namespace aal {

// compute gcd(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// long long ans = aal::gcd(28, 21LL, -7, 0);
// ans is 7
template <nonbool_integral... Ts> requires (sizeof...(Ts) >= 2)
[[nodiscard]] constexpr auto gcd(Ts... nums) noexcept
{
  return detail::gcd_lcm_impl<op::gcd<std::common_type_t<Ts...>>>(nums...);
}

// compute lcm(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// u128 ans = aal::lcm(28, -21, 7, 49, u128(1));
// ans is 588
template <nonbool_integral... Ts> requires (sizeof...(Ts) >= 2)
[[nodiscard]] constexpr auto lcm(Ts... nums) noexcept
{
  return detail::gcd_lcm_impl<op::lcm<std::common_type_t<Ts...>>>(nums...);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPERATION_GCD_INCLUDE_HPP
