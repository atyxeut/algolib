#ifndef AAL_SRC_MATH_INT_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP
#define AAL_SRC_MATH_INT_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-operation/overflow-detection/include.hpp */

#include <cassert>

#include "../../../concept/integral.hpp"
#include "detail.hpp"

namespace aal { namespace ioverflows {

// if a + b overflows the given result type, returns true
template <integral TResult, integral T1, integral T2>
[[nodiscard]] constexpr bool add(T1 a, T2 b) noexcept
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::selector<detail::mode::add, TResult>(a, b);
}

// if a * b overflows the given result type, returns true
template <integral TResult, integral T1, integral T2>
[[nodiscard]] constexpr bool mul(T1 a, T2 b) noexcept
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::selector<detail::mode::mul, TResult>(a, b);
}

}}// namespace aal::ioverflows

#endif // AAL_SRC_MATH_INT_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP
