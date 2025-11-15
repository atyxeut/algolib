#ifndef AAL_SRC_MATH_INT_OPS_DIV_INCLUDE_HPP
#define AAL_SRC_MATH_INT_OPS_DIV_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/div/include.hpp */

#include "detail.hpp"

// see note.md for extra information

namespace aal { namespace idiv {

// compute floor(a / b) for integers a, b without introducing floating-point numbers
// can correctly handle operands that have different width and signedness
//   int ans = aal::idiv::floor(5, 2);
//   int ans = aal::idiv::floor(-5, 2);
//   int ans = aal::idiv::floor(-2147483647 - 1, 1ull);
//   ans is 2, -3, -2147483648 respectively
template <typename T1, typename T2>
AAL_CONSTEXPR14 auto floor(T1 lhs, T2 rhs) noexcept ->
  typename std::enable_if<conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, detail::final_result_t<T1, T2>>::type
{
  assert(rhs != 0 && "divisor cannot be 0");
  return detail::selector<detail::mode::floor>(lhs, rhs);
}

// compute ceil(a / b) for integers a, b without introducing floating-point numbers
// can correctly handle operands that have different width and signedness
//   int ans = aal::idiv::ceil(5, 2); // 3
//   int ans = aal::idiv::ceil(-5, 2); // -2
//   long long ans = aal::idiv::ceil(-2147483647 - 1, -1); // 2147483648, no overflow
//   ans is 3, -2, 2147483648 (no overflow) respectively
template <typename T1, typename T2>
AAL_CONSTEXPR14 auto ceil(T1 lhs, T2 rhs) noexcept ->
  typename std::enable_if<conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, detail::final_result_t<T1, T2>>::type
{
  assert(rhs != 0 && "divisor cannot be 0");
  return detail::selector<detail::mode::ceil>(lhs, rhs);
}

}}// namespace aal::idiv

#endif // AAL_SRC_MATH_INT_OPS_DIV_INCLUDE_HPP
