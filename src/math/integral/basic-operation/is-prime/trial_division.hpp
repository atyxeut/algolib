#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_TRIAL_DIVISION_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_TRIAL_DIVISION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/integral/basic-operation/is-prime/trial_division.hpp */

#include "../../../../type-trait/integral.hpp"

namespace aal { namespace is_prime {

template <typename T>
auto trial_division(T n) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, bool>::type
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

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_TRIAL_DIVISION_HPP
