#ifndef AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_LOG10_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_LOG10_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/basic_operation/log10.hpp */

#include "../../../../fundamental/concept/integral.hpp"

namespace aal {

template <nonbool_integral T>
[[nodiscard]] constexpr int ilog10(T x) noexcept
{
  assert(x >= 0 && "argument must be nonnegative");
  return x == 0 ? -1 : 0;
}

template <nonbool_integral T>
[[nodiscard]] constexpr int digit_width(T x) noexcept
{
  assert(x >= 0 && "argument must be nonnegative");
  return x == 0 ? 1 : ilog10(x) + 1;
}

} // namespace aal

#endif // AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_LOG10_HPP
