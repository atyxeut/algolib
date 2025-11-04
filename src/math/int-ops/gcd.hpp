#ifndef AAL_SRC_MATH_INT_OPS_GCD_HPP
#define AAL_SRC_MATH_INT_OPS_GCD_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/gcd.hpp */

#include "../operator/gcd.hpp"
#include "detail/gcd.hpp"
#include <utility>

// see gcd.md for extra information

namespace aal {

// compute gcd(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// long long ans = aal::gcd(28, 21LL, -7, 0);
// ans is 7
template <typename... Ts>
AAL_CONSTEXPR14 auto gcd(Ts&&... nums) noexcept ->
  typename std::enable_if<conjunction<is_nonbool_integral<Ts>...>::value, typename std::common_type<remove_cv_t<Ts>...>::type>::type
{
  using result_type = typename std::common_type<remove_cv_t<Ts>...>::type;
  return detail::gcd_lcm_selector<op::gcd<result_type>>(std::forward<Ts>(nums)...);
}

// compute lcm(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// u128 ans = aal::lcm(28, -21, 7, 49, u128(1));
// ans is 588
template <typename... Ts>
AAL_CONSTEXPR14 auto lcm(Ts&&... nums) noexcept ->
  typename std::enable_if<conjunction<is_nonbool_integral<Ts>...>::value, typename std::common_type<remove_cv_t<Ts>...>::type>::type
{
  using result_type = typename std::common_type<remove_cv_t<Ts>...>::type;
  return detail::gcd_lcm_selector<op::lcm<result_type>>(std::forward<Ts>(nums)...);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_GCD_HPP
