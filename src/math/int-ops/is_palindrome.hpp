#ifndef AAL_SRC_MATH_INT_OPS_IS_PALINDROME_HPP
#define AAL_SRC_MATH_INT_OPS_IS_PALINDROME_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-ops/is_palindrome.hpp */

#include "../../concepts/integral.hpp"

namespace aal {

template <nonbool_integral T>
[[nodiscard]] constexpr bool is_palindrome(T n) noexcept
{
  if (n == 0)
    return true;

  if (n < 0 || n % 10 == 0)
    return false;

  T r = 0;
  while (n > r) {
    r = r * 10 + n % 10;
    n /= 10;
  }

  return r == n || r / 10 == n;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_IS_PALINDROME_HPP
