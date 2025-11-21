#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_NONNEGATIVE_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_NONNEGATIVE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic-operation/overflow-detection/nonnegative.hpp */

#include <limits>

#include "../../../../concept/integral.hpp"

namespace aal::ioverflows::nonnegative {

template <integral TResult>
[[nodiscard]] constexpr bool add(u128 a, u128 b) noexcept
{
  auto max = static_cast<u128>(std::numeric_limits<TResult>::max());
  return b > max || a > max - b;
}

template <integral TResult>
[[nodiscard]] constexpr bool mul(u128 a, u128 b) noexcept
{
  auto max = static_cast<u128>(std::numeric_limits<TResult>::max());
  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
  return b == 0 ? false : a > max / b;
}

}// namespace aal::ioverflows::nonnegative

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_NONNEGATIVE_HPP
