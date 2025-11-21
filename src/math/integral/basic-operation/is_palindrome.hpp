#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PALINDROME_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PALINDROME_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic-operation/is_palindrome.hpp */

#include "../../../concept/integral.hpp"

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

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PALINDROME_HPP
