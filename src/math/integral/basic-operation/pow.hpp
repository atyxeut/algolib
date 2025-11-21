#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic-operation/pow.hpp */

#include "../../operator/ipow/include.hpp"

namespace aal {

template <nonbool_integral T1, nonbool_integral T2>
[[nodiscard]] constexpr T1 ipow(T1 a, T2 n) noexcept
{
  assert(n >= 0 && "exponent must be nonnegative");
  return op::ipow<T1, make_unsigned_t<T2>>::operator ()(a, n);
}

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP
