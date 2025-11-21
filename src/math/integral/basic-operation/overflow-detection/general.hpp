#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_GENERAL_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_GENERAL_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic-operation/overflow-detection/general.hpp */

#include <limits>

#include "../../../../concept/integral.hpp"

namespace aal::ioverflows::general {

template <integral TResult, unsigned_integral T>
[[nodiscard]] constexpr bool add(T a_, T b_) noexcept
{
  auto a = static_cast<u128>(a_);
  auto b = static_cast<u128>(b_);
  auto max = static_cast<u128>(std::numeric_limits<TResult>::max());

  return b > max || a > max - b;
}

template <integral TResult, unsigned_integral T>
[[nodiscard]] constexpr bool mul(T a_, T b_) noexcept
{
  auto a = static_cast<u128>(a_);
  auto b = static_cast<u128>(b_);
  auto max = static_cast<u128>(std::numeric_limits<TResult>::max());

  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
  return b == 0 ? false : a > max / b;
}

} // namespace aal::ioverflows::general

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_GENERAL_HPP
