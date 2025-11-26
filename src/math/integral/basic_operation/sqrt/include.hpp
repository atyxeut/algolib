#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_SQRT_INCLUDE_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_SQRT_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic_operation/sqrt/include.hpp */

#include <algorithm>
#include <cassert>

#include "../../../../concept/integral.hpp"

namespace aal {

// compute floor(sqrt(x)) without introducing floating-point numbers
template <nonbool_integral T>
[[nodiscard]] constexpr T isqrt(T x) noexcept
{
  assert(x >= 0 && "argument must be nonnegative");

  if (x == 0 || x == 1)
    return x;

  T cur;
  T nxt = x;
  do {
    cur = nxt;
    nxt = (cur + x / cur) / 2;
  } while (cur > nxt);

  return std::min(cur, nxt);
}

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_SQRT_INCLUDE_HPP
