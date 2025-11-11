#ifndef AAL_SRC_MATH_INT_OPS_SQRT_HPP
#define AAL_SRC_MATH_INT_OPS_SQRT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/sqrt.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type-traits/integral.hpp"
#include <algorithm>
#include <cassert>

namespace aal {

// compute floor(sqrt(x)) without introducing floating-point numbers, see isqrt.md for extra information
template <typename T>
AAL_CONSTEXPR14 auto isqrt(T x) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, T>::type
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

#endif // AAL_SRC_MATH_INT_OPS_SQRT_HPP
