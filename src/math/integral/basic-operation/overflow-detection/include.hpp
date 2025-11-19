#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/integral/basic-operation/overflow-detection/include.hpp */

#include <cassert>

#include "../../../../type-trait/integral.hpp"
#include "detail.hpp"

namespace aal { namespace overflows {

// if a + b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
auto iadd(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<TResult>, is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::iselector<detail::imode::add, TResult>(a, b);
}

// if a * b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
auto imul(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<TResult>, is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::iselector<detail::imode::mul, TResult>(a, b);
}

}} // namespace aal::ioverflows

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_INCLUDE_HPP
