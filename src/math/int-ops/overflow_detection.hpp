#ifndef AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_HPP
#define AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/overflow_detection.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type-traits/integral.hpp"
#include <cassert>
#include <limits>

namespace aal {

// if a + b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 auto iadd_overflows(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return b > std::numeric_limits<TResult>::max() || a > std::numeric_limits<TResult>::max() - b;
}

// if a * b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 auto imul_overflows(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return b == 0 ? false : a > std::numeric_limits<TResult>::max() / b;
  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_HPP
