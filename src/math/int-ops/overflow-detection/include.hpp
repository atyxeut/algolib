#ifndef AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_INCLUDE_HPP
#define AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-ops/overflow-detection/include.hpp */

#include "../../../type-traits/integral.hpp"
#include "detail.hpp"
#include <cassert>

namespace aal {

// if a + b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 auto iadd_overflows(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::ioverflow::selector<detail::ioverflow::mode::add, TResult>(a, b);
}

// if a * b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 auto imul_overflows(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::ioverflow::selector<detail::ioverflow::mode::mul, TResult>(a, b);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_OVERFLOW_DETECTION_INCLUDE_HPP
