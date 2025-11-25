#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PALINDROME_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PALINDROME_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/integral/basic-operation/is_palindrome.hpp */

#include "../../../type-trait/integral.hpp"

namespace aal {

// test if a nonnegative integer is palindrome
template <typename T>
auto is_palindrome(T n) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, bool>::type
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
