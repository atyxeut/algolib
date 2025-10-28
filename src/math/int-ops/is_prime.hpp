#ifndef AAL_SRC_MATH_INT_OPS_IS_PRIME_HPP
#define AAL_SRC_MATH_INT_OPS_IS_PRIME_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/is_prime.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type-traits/integral.hpp"

namespace aal { namespace is_prime {

// test if an integer is prime using trial division
template <typename T>
AAL_CONSTEXPR14 bool trial_division(T n) noexcept
{
  static_assert(is_nonbool_integral<T>::value, "argument must be nonbool integer");

  if (n == 2)
    return true;

  if (n < 2 || n % 2 == 0)
    return false;

  // let p be the smallest prime factor of n, write n = p * a, then p <= a ==> p * p <= p * a = n ==> p <= sqrt(n)
  for (T i = 3; i <= n / i; i += 2) {
    if (n % i == 0)
      return false;
  }
  return true;
}

// template <typename T>
// AAL_CONSTEXPR14 bool miller_rabin(T n) noexcept
// {
//   static_assert(is_nonbool_integral<T>::value, "argument must be nonbool integer");
// }

}} // namespace aal::is_prime

#endif // AAL_SRC_MATH_INT_OPS_IS_PRIME_HPP
