#ifndef AAL_SRC_MATH_OVERFLOW_DETECTION_HPP
#define AAL_SRC_MATH_OVERFLOW_DETECTION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops/overflow_detection.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type_traits/integral.hpp"
#include <cassert>
#include <limits>

namespace aal {

// if a + b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 bool iadd_overflows(T1 a, T2 b) noexcept
{
  static_assert(conjunction<is_integral<T1>, is_integral<T2>>::value, "operands must be integers");
  assert(a >= 0 && b >= 0 && "operands must be nonnegative");
  return b > std::numeric_limits<TResult>::max() || a > std::numeric_limits<TResult>::max() - b;
}

// if a * b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 bool imul_overflows(T1 a, T2 b) noexcept
{
  static_assert(conjunction<is_integral<T1>, is_integral<T2>>::value, "operands must be integers");
  assert(a >= 0 && b >= 0 && "operands must be nonnegative");
  return b == 0 ? false : a > std::numeric_limits<TResult>::max() / b;
  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
}

} // namespace aal

#endif // AAL_SRC_MATH_OVERFLOW_DETECTION_HPP
