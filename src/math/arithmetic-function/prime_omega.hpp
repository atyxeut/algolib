#ifndef AAL_SRC_MATH_ARITHMETIC_FUNCTION_PRIME_OMEGA_HPP
#define AAL_SRC_MATH_ARITHMETIC_FUNCTION_PRIME_OMEGA_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/arithmetic-function/prime_omega.hpp */

#include "../../type-trait/integral.hpp"
#include <cassert>

// see https://en.wikipedia.org/wiki/Prime_omega_function#Properties_and_relations for extra information

namespace aal { namespace arith_func {

template <typename T>
auto little_omega(T n) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, T>::type
{
  assert(n > 0 && "argument must be positive");

  T ans = 0;
  for (T i = 2; i <= n / i; ++i) {
    ans += n % i == 0;
    while (n % i == 0)
      n /= i;
  }
  return ans += n > 1;
}

template <typename T>
auto big_omega(T n) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, T>::type
{
  assert(n > 0 && "argument must be positive");

  T ans = 0;
  for (T i = 2; i <= n / i; ++i) {
    while (n % i == 0) {
      ++ans;
      n /= i;
    }
  }
  return ans += n > 1;
}

}} // namespace aal::arith_func

#endif // AAL_SRC_MATH_ARITHMETIC_FUNCTION_PRIME_OMEGA_HPP
