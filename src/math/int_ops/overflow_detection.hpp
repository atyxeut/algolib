#ifndef AAL_SRC_MATH_OVERFLOW_DETECTION_HPP
#define AAL_SRC_MATH_OVERFLOW_DETECTION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/overflow_detection.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type_traits/integral.hpp"
#include <cassert>
#include <limits>

namespace aal {

template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 bool iadd_overflows(T1 lhs, T2 rhs) noexcept
{
  static_assert(conjunction<is_integral<T1>, is_integral<T2>>::value, "given operands must be integers");
  assert(lhs >= 0 && rhs >= 0 && "given operands must be nonnegative");
  return rhs > ::std::numeric_limits<TResult>::max() || lhs > ::std::numeric_limits<TResult>::max() - rhs;
}

template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 bool imul_overflows(T1 lhs, T2 rhs) noexcept
{
  static_assert(conjunction<is_integral<T1>, is_integral<T2>>::value, "given operands must be integers");
  assert(lhs >= 0 && rhs >= 0 && "given operands must be nonnegative");
  return rhs == 0 ? false : lhs > ::std::numeric_limits<TResult>::max() / rhs;
}

} // namespace aal

#endif // AAL_SRC_MATH_OVERFLOW_DETECTION_HPP
