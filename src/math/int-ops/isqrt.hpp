#ifndef AAL_SRC_MATH_INT_OPS_ISQRT_HPP
#define AAL_SRC_MATH_INT_OPS_ISQRT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/isqrt.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type-traits/integral.hpp"
#include <algorithm>
#include <cassert>

namespace aal {

template <typename T>
AAL_CONSTEXPR14 T isqrt(T x) noexcept
{
  static_assert(is_nonbool_integral<T>::value, "operand must be nonbool integer");
  assert(x >= 0 && "operand must be nonnegative");

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

#endif // AAL_SRC_MATH_INT_OPS_ISQRT_HPP
