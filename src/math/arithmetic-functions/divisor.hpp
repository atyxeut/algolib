#ifndef AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_DIVISOR_HPP
#define AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_DIVISOR_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/arithmetic-functions/divisor.hpp */

#include "../int-ops/ipow.hpp"

// see https://en.wikipedia.org/wiki/Divisor_function#Formulas_at_prime_powers for extra information

namespace aal { namespace arith_func {

template <int x = 1, typename T>
AAL_CONSTEXPR14 T sigma(T n) noexcept
{
  static_assert(is_nonbool_integral<T>::value, "argument must be integer");
  assert(n > 0 && "argument must be positive");

  T ans = 0;
  for (T i = 1; i <= n / i; ++i) {
    if (n % i == 0) {
      ans += ipow(i, x);
      if (n / i != i)
        ans += ipow(n / i, x);
    }
  }
  return ans;
}

}} // namespace aal::arith_func

#endif // AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_DIVISOR_HPP
