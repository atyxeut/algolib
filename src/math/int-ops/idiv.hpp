#ifndef AAL_SRC_MATH_INT_OPS_IDIV_HPP
#define AAL_SRC_MATH_INT_OPS_IDIV_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/idiv.hpp */

#include "detail/idiv.hpp"

// see idiv.md for extra information

namespace aal {

// compute floor(a / b) for integers a, b without introducing floating-point numbers
// can correctly handle operands that have different width and signedness
// int ans = aal::idiv_floor(5, 2);
// int ans = aal::idiv_floor(-5, 2);
// int ans = aal::idiv_floor(-2147483647 - 1, 1ull);
// ans is 2, -3, -2147483648 respectively
template <typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_floor(T1 lhs, T2 rhs) noexcept ->
  typename std::enable_if<conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, detail::idiv::final_result_t<T1, T2>>::type
{
  assert(rhs != 0 && "divisor cannot be 0");
  return detail::idiv::selector<detail::idiv::mode::floor>(lhs, rhs);
}

// compute ceil(a / b) for integers a, b without introducing floating-point numbers
// can correctly handle operands that have different width and signedness
// int ans = aal::idiv_ceil(5, 2); // 3
// int ans = aal::idiv_ceil(-5, 2); // -2
// long long ans = aal::idiv_ceil(-2147483647 - 1, -1); // 2147483648, no overflow
// ans is 3, -2, 2147483648 (no overflow) respectively
template <typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_ceil(T1 lhs, T2 rhs) noexcept ->
  typename std::enable_if<conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, detail::idiv::final_result_t<T1, T2>>::type
{
  assert(rhs != 0 && "divisor cannot be 0");
  return detail::idiv::selector<detail::idiv::mode::ceil>(lhs, rhs);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_IDIV_HPP
