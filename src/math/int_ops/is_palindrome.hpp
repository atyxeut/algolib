#ifndef AAL_SRC_MATH_INT_OPS_IS_PALINDROME_HPP
#define AAL_SRC_MATH_INT_OPS_IS_PALINDROME_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops/is_palindrome.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type_traits/integral.hpp"

namespace aal {

template <typename T>
AAL_CONSTEXPR14 bool is_palindrome(T n) noexcept
{
  static_assert(is_nonbool_integral<T>::value, "operand must be nonbool integer");

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
