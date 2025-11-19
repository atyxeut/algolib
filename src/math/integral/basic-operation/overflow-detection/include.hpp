#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/integral/basic-operation/overflow-detection/include.hpp */

#include <cassert>

#include "../../../../concept/integral.hpp"
#include "detail.hpp"

namespace aal { namespace overflows {

// if a + b overflows the given result type, returns true
template <integral TResult, integral T1, integral T2>
[[nodiscard]] constexpr bool iadd(T1 a, T2 b) noexcept
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::iselector<detail::imode::add, TResult>(a, b);
}

// if a * b overflows the given result type, returns true
template <integral TResult, integral T1, integral T2>
[[nodiscard]] constexpr bool imul(T1 a, T2 b) noexcept
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::iselector<detail::imode::mul, TResult>(a, b);
}

}}// namespace aal::overflows

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP
