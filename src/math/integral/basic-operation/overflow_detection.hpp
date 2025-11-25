#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/integral/basic-operation/overflow_detection.hpp */

#include "../../../alias/integral.hpp"

namespace aal { namespace ioverflows {

constexpr bool add(u128 a, u128 b, u128 max) noexcept
{
  return b > max || a > max - b;
}

constexpr bool mul(u128 a, u128 b, u128 max) noexcept
{
  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
  return b == 0 ? false : a > max / b;
}

}} // namespace aal::ioverflows

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_HPP
