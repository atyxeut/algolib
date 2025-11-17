#ifndef AAL_SRC_MATH_INT_OPERATION_SQRT_INCLUDE_HPP
#define AAL_SRC_MATH_INT_OPERATION_SQRT_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-operation/sqrt/include.hpp */

#include "../../../concept/integral.hpp"
#include <algorithm>
#include <cassert>

namespace aal {

// compute floor(sqrt(x)) without introducing floating-point numbers, see note.md for extra information
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

#endif // AAL_SRC_MATH_INT_OPERATION_SQRT_INCLUDE_HPP
