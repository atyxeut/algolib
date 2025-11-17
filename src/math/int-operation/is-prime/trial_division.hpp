#ifndef AAL_SRC_MATH_INT_OPERATION_IS_PRIME_TRIAL_DIVISION_HPP
#define AAL_SRC_MATH_INT_OPERATION_IS_PRIME_TRIAL_DIVISION_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-operation/is-prime/trial_division.hpp */

#include "../../../concept/integral.hpp"

namespace aal { namespace is_prime {

template <nonbool_integral T>
[[nodiscard]] constexpr bool trial_division(T n) noexcept
{
  if (n == 2)
    return true;

  if (n < 2 || n % 2 == 0)
    return false;

  // let p be the smallest prime factor of n, write n = p * a, then p <= a ==> p * p <= p * a = n ==> p <= sqrt(n)
  for (T i = 3; i <= n / i; i += 2)
    if (n % i == 0)
      return false;

  return true;
}

}} // namespace aal::is_prime

#endif // AAL_SRC_MATH_INT_OPERATION_IS_PRIME_TRIAL_DIVISION_HPP
