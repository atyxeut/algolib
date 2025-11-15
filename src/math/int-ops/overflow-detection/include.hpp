#ifndef AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_INCLUDE_HPP
#define AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/overflow-detection/include.hpp */

#include "../../../type-traits/integral.hpp"
#include "detail.hpp"
#include <cassert>

namespace aal { namespace ioverflows {

// if a + b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
auto add(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<TResult>, is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::selector<detail::mode::add, TResult>(a, b);
}

// if a * b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
auto mul(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<TResult>, is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::selector<detail::mode::mul, TResult>(a, b);
}

}} // namespace aal::ioverflows

#endif // AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_INCLUDE_HPP
